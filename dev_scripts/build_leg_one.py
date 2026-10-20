#!/usr/bin/env python3
"""Generate the hometown's maps, event text and scripts from reviewed dialogue.
Run from repository root. Assets use the existing Emerald tilesets.
"""
from pathlib import Path
import json, struct, textwrap, re
ROOT=Path(__file__).resolve().parents[1]
def write_if_changed(p,s):
 if not p.exists() or p.read_text(encoding='utf8') != s:p.write_text(s,encoding='utf8')
def put(p,s):
 p=ROOT/p;p.parent.mkdir(parents=True,exist_ok=True);write_if_changed(p,s)
def jput(p,v):put(p,json.dumps(v,indent=2)+'\n')
def load(p):return json.loads((ROOT/p).read_text())
D=load('data/our-game/dialogue.json')
# 28 columns conservatively fit FONT_NORMAL, with space reserved for names.
def wrap(s):
 s=s.replace('Pokémon','POKéMON').replace('Pokédex','POKéDEX').replace('’',"'").replace('—','--')
 pages=[]
 for para in s.split('\n\n'):
  lines=[]
  for line in para.splitlines():
   lines+=textwrap.wrap(line,28,break_long_words=False,break_on_hyphens=False) or ['']
  pages += ['\\n'.join(lines[i:i+2]) for i in range(0,len(lines),2)]
 return '\\p'.join(pages)
texts='@ Generated from data/our-game/dialogue.json; edit that file, then regenerate.\n'
for k,v in D.items():texts+=f'Leg_Text_{k}::\n\t.string "'+wrap(v).replace('"','\\"')+'$"\n\n'
put('data/our-game/text.inc',texts)
# Canonical dialogue export remains readable independently of ROM formatting.
ref=['LEG ONE: APPROVED OPENING AND HOMETOWN DIALOGUE','Revision: 2026-10-20','',
'Latest board edits take precedence over earlier drafts. Astrid and Edwulf have already departed when their houses can be visited. Their parents remain. Neville is still packing. The old man uses the revised monologue below.',
'PC+Neville oppose Astrid+Edwulf in a level-5 supervised double battle. Win and loss both continue. No permadeath for this battle.',
'Five candidates: Vulpix, Psyduck, Phanpy, Crabrawler, Deerling. Unchanged generation-9 level-up moves. No early impactful TMs or Infinite Repel.',
'All introductory character/name selections occur in the opening interface. Yew addresses the group; the lab reveal follows.',
'Opening speech:','YEW: Hello, children. Welcome.','My name is Professor Yew. I oversee the Pokémon Training Program here in our region.',
'Today, the day you have been waiting for is finally here. You begin your first steps as Pokémon trainers.',
'Our world is home to remarkable creatures called Pokémon. Some live alongside us. Others make their homes in the wild.',
'They are our friends and companions. Together, we soar above the clouds, cross vast oceans, light our cities, and make gardens bloom.',
'Pokémon help us heal the sick, create beautiful music, discover new places, and accomplish things we could never dream of doing alone.',
'And, of course, they love a good battle!','As trainers, you will learn to bring out your partners’ remarkable gifts.',
'The places you discover, the challenges you overcome, and the victories you share will build the strongest bonds between you.',
'A Pokémon journey is the beginning of a friendship that can last a lifetime.',
'Before we begin, let’s make sure your enrollment details are correct.','[Appearance selection] And your name? [Name entry] {PLAYER}. Good.',
'Please review your training preferences. [Settings, optional Nuzlocke configuration and rule lock.] Everything in order? Then we can begin.',
'','STARTER ASSIGNMENTS (PC / Neville / Astrid / Edwulf / Unused)',
'Vulpix / Phanpy / Psyduck / Deerling / Crabrawler','Psyduck / Phanpy / Deerling / Crabrawler / Vulpix',
'Phanpy / Psyduck / Deerling / Crabrawler / Vulpix','Crabrawler / Vulpix / Psyduck / Phanpy / Deerling',
'Deerling / Psyduck / Vulpix / Crabrawler / Phanpy','',
'CONVERSATION FLOW','Lab: Welcome to ReadyN, battle, WinN/WinA/WinY OR LoseA/LoseE/LoseA2/LoseN/LoseY, then Rested through MeetNeville.',
'Challenge choice: “We heard her.” -> Heard; “You two can take notes for us.” -> Notes.',
'Mom choice: “We won our first battle.” (only after win) or “We had our first battle.” -> respective response.',
'Neville choice: “She knows you.” or “Any food in there?” -> respective response.',
'Edwulf parents choice: “They didn’t say.” or “I’m sure we can.” -> respective response.',
'Optional visits, not mandatory sightseeing. Only Mom farewell is required before departure.',
'','DIALOGUE TEXT (scene labels are implementation identifiers)']
for k,v in D.items():ref+=['',f'[{k}]',v]
put('docs/our-game/Leg-One-Dialogue.txt','\n'.join(ref)+'\n')
# Fresh layout: six houses around a central path, reuse proven 4x4 exterior.
L=load('data/layouts/layouts.json'); byid={x['id']:x for x in L['layouts']}
def binread(p):b=(ROOT/p).read_bytes();return list(struct.unpack('<'+'H'*(len(b)//2),b))
def binsave(p,a):p=ROOT/p;p.parent.mkdir(parents=True,exist_ok=True);b=struct.pack('<'+'H'*len(a),*a);p.write_bytes(b) if not p.exists() or p.read_bytes()!=b else None
orig=binread('data/layouts/PocVillage/map.bin')
# Stable exterior literal from the original POC; idempotent.
house=[[0x326c,0x326d,0x326d,0x326e],[0x0674,0x0675,0x0675,0x0676],[0x067c,0x067f,0x067d,0x067e],[0x0684,0x0687,0x068f,0x0686]]
w,h=40,36;a=[0x3001]*(w*h)
for y in range(h):
 for x in range(w):
  if x<2 or x>=w-2 or y>=h-2 or (y<2 and not 18<=x<22):a[y*w+x]=[[0x05d4,0x05d5],[0x05dc,0x05dd]][y%2][x%2]
  if 18<=x<22 and y<h-2:a[y*w+x]=0x31d9
houses=[('LegOldMan',4,5),('LegEdwulf',27,5),('LegNeville',4,15),('LegAstrid',27,15),('LegHome',4,25),('LegLab',27,25)]
for name,x,y in houses:
 for dy in range(4):
  for dx in range(4):a[(y+dy)*w+x+dx]=house[dy][dx]
 for xx in range(min(x+1,18),max(x+3,22)):a[(y+4)*w+xx]=0x31d9;a[(y+5)*w+xx]=0x31d9
 a[(y+4)*w+x+1]=0x31d9
 # Sign next to each entrance.
 a[(y+4)*w+x+4]=0x0403
binsave('data/layouts/PocVillage/map.bin',a)
byid['LAYOUT_POC_VILLAGE'].update(width=w,height=h)
# Route boundary only, future gameplay continues north in a later build.
a=[0x3001]*(40*12)
for y in range(12):
 for x in range(40):
  if not 18<=x<22:a[y*40+x]=[[0x05d4,0x05d5],[0x05dc,0x05dd]][y%2][x%2]
  else:a[y*40+x]=0x31d9
# A closed northern end with readable sign.
for x in range(18,22):a[1*40+x]=0x0403
binsave('data/layouts/PocTrail/map.bin',a);byid['LAYOUT_POC_TRAIL'].update(width=40,height=12)
# Expanded laboratory: five physical balls on a counter and a practice floor.
j=byid['LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB'];a=[0x3202]*(17*18)
for y in range(18):
 for x in range(17):
  if y<2:a[y*17+x]=0x0401
  if x in [0,16] or y==17:a[y*17+x]=0x0401
for x in range(4,14):
 a[4*17+x]=0x0400+(624 if x%2==0 else 625)
 a[5*17+x]=0x0400+(636 if x%2==0 else 637)
for y in range(10,16):
 for x in range(3,14):a[y*17+x]=0x3203
# Desk for the devices and a normal southern doorway.
a[2*17+7]=0x0400+624;a[2*17+8]=0x0400+625
a[17*17+8]=0x0206;a[17*17+9]=0x0207
binsave('data/layouts/LegLab/map.bin',a);binsave('data/layouts/LegLab/border.bin',[0x0201]*4)
entry=dict(j,id='LAYOUT_LEG_LAB',name='LegLab_Layout',width=17,height=18,blockdata_filepath='data/layouts/LegLab/map.bin',border_filepath='data/layouts/LegLab/border.bin')
if 'LAYOUT_LEG_LAB' in byid:byid['LAYOUT_LEG_LAB'].update(entry)
else:L['layouts'].append(entry)
j=byid['LAYOUT_HOUSE1'];a=binread(j['blockdata_filepath'])
for y in range(3,8):
 for x in [1,8]:a[y*j['width']+x]=0x3201
entry=dict(j,id='LAYOUT_LEG_EDWULF',name='LegEdwulf_Layout',blockdata_filepath='data/layouts/LegEdwulf/map.bin')
binsave(entry['blockdata_filepath'],a)
if 'LAYOUT_LEG_EDWULF' in byid:byid['LAYOUT_LEG_EDWULF'].update(entry)
else:L['layouts'].append(entry)
jput('data/layouts/layouts.json',L)
# Maps.
def obj(gfx,x,y,script,flag='0',face='DOWN'):
 return dict(graphics_id='OBJ_EVENT_GFX_'+gfx,x=x,y=y,elevation=3,movement_type='MOVEMENT_TYPE_FACE_'+face,movement_range_x=0,movement_range_y=0,trainer_type='TRAINER_TYPE_NONE',trainer_sight_or_berry_tree_id='0',script=script,flag=flag)
def warp(x,y,m,i):return dict(x=x,y=y,elevation=0,dest_map=m,dest_warp_id=str(i))
def bg(x,y,s):return dict(type='sign',x=x,y=y,elevation=0,player_facing_dir='BG_EVENT_PLAYER_FACING_ANY',script=s)
def trigger(x,y,var,value,s):return dict(type='trigger',x=x,y=y,elevation=3,var=var,var_value=str(value),script=s)
def mapbase(name,layout):
 m=load('data/maps/PocCabin/map.json');m.update(id='MAP_'+re.sub(r'(?<!^)(?=[A-Z])','_',name).upper(),name=name,layout=layout,object_events=[],warp_events=[],coord_events=[],bg_events=[]);return m
v=load('data/maps/PocVillage/map.json');v.update(object_events=[],warp_events=[],coord_events=[],bg_events=[])
for i,(name,x,y) in enumerate(houses):
 v['warp_events'].append(warp(x+1,y+3,'MAP_'+re.sub(r'(?<!^)(?=[A-Z])','_',name).upper(),0))
 v['bg_events'].append(bg(x+4,y+4,'Leg_Sign_'+name))
 if name=='LegLab':m=mapbase(name,'LAYOUT_LEG_LAB')
 else:m=mapbase(name,'LAYOUT_HOUSE1')
 if name=='LegLab':
  m['music']='MUS_BIRCH_LAB';m['warp_events']=[warp(8,17,'MAP_POC_VILLAGE',i),warp(9,17,'MAP_POC_VILLAGE',i)]
  m['object_events']=[obj('LEG_YEW',8,3,'LegLab_Yew'),obj('LEG_NEVILLE',6,7,'LegLab_Classmate','FLAG_LEG_CLASS_LEFT','UP'),obj('LEG_ASTRID',9,7,'LegLab_Classmate','FLAG_LEG_CLASS_LEFT','UP'),obj('LEG_EDWULF',10,7,'LegLab_Classmate','FLAG_LEG_CLASS_LEFT','UP')]
  for k in range(5):m['object_events'].append(obj('ITEM_BALL',4+2*k,5,'LegLab_Ball'+str(k),'FLAG_LEG_BALL_'+str(k)))
  m['bg_events']=[bg(2,2,'Leg_Preferences')]
  m['coord_events']=[trigger(x,6,'VAR_LEG_STAGE',2,'LegLab_Table') for x in range(4,14)]
  for x in [8,9]:
   for stage in [2,5]:m['coord_events'].append(trigger(x,16,'VAR_LEG_STAGE',stage,'LegLab_NoExit'))
 else:
  m['warp_events']=[warp(3,8,'MAP_POC_VILLAGE',i),warp(4,8,'MAP_POC_VILLAGE',i)]
  if name=='LegHome':
   m['layout']='LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F';m['object_events']=[obj('MOM',7,4,'LegHome_Mom')];m['warp_events']=[warp(8,8,'MAP_POC_VILLAGE',i),warp(9,8,'MAP_POC_VILLAGE',i),warp(8,2,'MAP_LEG_HOME_UPSTAIRS',0)]
  if name=='LegOldMan':m['object_events']=[obj('OLD_MAN',8,4,'LegOldMan_Talk')]
  if name=='LegAstrid':m['object_events']=[obj('WOMAN_1',8,4,'LegAstrid_Parent')]
  if name=='LegEdwulf':
   m['layout']='LAYOUT_LEG_EDWULF';m['object_events']=[obj('WOMAN_3',1,5,'LegEdwulf_Parent',face='RIGHT'),obj('MAN_1',5,4,'LegEdwulf_Again',face='LEFT')]
  if name=='LegNeville':m['object_events']=[obj('WOMAN_1',8,4,'LegNeville_Mother'),obj('LEG_NEVILLE',8,6,'LegNeville_Talk','FLAG_LEG_NEVILLE_LEFT')]
 jput('data/maps/'+name+'/map.json',m)
v['object_events']=[obj('MAN_1',17,21,'Leg_Resident'),obj('SCIENTIST_1',23,29,'Leg_Worker'),obj('MAN_2',16,15,'Leg_FastLevel'),obj('BOY_1',23,15,'Leg_SetMoves'),obj('LITTLE_BOY',22,4,'Leg_Child'),obj('WOMAN_1',17,9,'Leg_Guide')]
v['bg_events'].append(bg(22,2,'Leg_Boundary'))
for x in range(18,22):v['coord_events'].append(trigger(x,2,'VAR_LEG_FAREWELL',0,'Leg_NeedMom'))
jput('data/maps/PocVillage/map.json',v)
t=load('data/maps/PocTrail/map.json');t.update(object_events=[],coord_events=[],bg_events=[bg(x,1,'Leg_Complete') for x in range(18,22)])
for x in range(18,22):t['coord_events'].append(trigger(x,10,'VAR_LEG_COMPLETE',0,'Leg_Complete'))
jput('data/maps/PocTrail/map.json',t)
m=mapbase('LegHomeUpstairs','LAYOUT_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F');m['warp_events']=[warp(7,1,'MAP_LEG_HOME',2)];m['bg_events']=[bg(1,4,'LegHome_Bed'),bg(1,1,'LegHome_PC')];jput('data/maps/LegHomeUpstairs/map.json',m)
G=load('data/maps/map_groups.json');G['gMapGroup_Poc']=['PocVillage','PocTrail','PocCabin']+[x[0] for x in houses]+['LegHomeUpstairs'];jput('data/maps/map_groups.json',G)
# Flags/vars: all were explicitly unused in this version.
p=ROOT/'include/constants/flags.h';s=p.read_text();flags={'FLAG_LEG_CLASS_LEFT':0x22,'FLAG_LEG_NEVILLE_LEFT':0x23,'FLAG_LEG_MOM_GIFT':0x24,'FLAG_LEG_OLD_TALKED':0x25,'FLAG_LEG_ED_TALKED':0x26,'FLAG_LEG_NEV_TALKED':0x27,'FLAG_LEG_NICKNAME':0x28,'FLAG_LEG_FAST_LEVEL':0x29,'FLAG_LEG_SET_MOVES':0x2a,'FLAG_LEG_BALL_0':0x2b,'FLAG_LEG_BALL_1':0x2c,'FLAG_LEG_BALL_2':0x2d,'FLAG_LEG_BALL_3':0x2e,'FLAG_LEG_BALL_4':0x2f,'FLAG_LEG_LAB_WON':0x30}
for name,value in flags.items():s=re.sub(r'#define (?:FLAG_UNUSED_0x0'+f'{value:02X}'+r'|'+name+r')\s+[^\n]+',f'#define {name:<33} 0x{value:02X} // Leg one',s)
write_if_changed(p,s)
p=ROOT/'include/constants/vars.h';s=p.read_text()
for value,name in {0x40f7:'VAR_TRAINER_LEVEL',0x40f8:'VAR_LEG_FAREWELL',0x40f9:'VAR_LEG_COMPLETE',0x40fa:'VAR_LEG_STAGE',0x40fb:'VAR_LEG_REPLY'}.items():s=re.sub(r'#define (?:VAR_UNUSED_0x'+f'{value:04X}'+r'|'+name+r')\s+[^\n]+',f'#define {name:<53} 0x{value:04X} // Leg one',s)
write_if_changed(p,s)
# Start in the laboratory; respawn outside the lab after future battles.
p=ROOT/'src/new_game.c';s=p.read_text().replace('MAP_GROUP(MAP_POC_VILLAGE), MAP_NUM(MAP_POC_VILLAGE), WARP_ID_NONE, 9, 12','MAP_GROUP(MAP_LEG_LAB), MAP_NUM(MAP_LEG_LAB), WARP_ID_NONE, 6, 7');s=re.sub(r'(MAP_GROUP\(MAP_LEG_LAB\), MAP_NUM\(MAP_LEG_LAB\), WARP_ID_NONE, )\d+, \d+',r'\g<1>7, 7',s);write_if_changed(p,s)
p=ROOT/'src/data/heal_locations.json';js=json.loads(p.read_text())
# Locate nested heal location without depending on generated ordering.
def editheal(v):
 if isinstance(v,dict):
  if v.get('id')=='HEAL_LOCATION_POC_VILLAGE' or v.get('map')=='MAP_POC_VILLAGE':
   if 'x' in v:v['x']=28
   if 'y' in v:v['y']=29
  for c in v.values():editheal(c)
 elif isinstance(v,list):
  for c in v:editheal(c)
editheal(js);jput('src/data/heal_locations.json',js)
# Human-readable temporary section labels, pending final town names.
p=ROOT/'src/data/region_map/region_map_sections.json';s=p.read_text().replace('Demo Village','Hometown').replace('DEMO VILLAGE','HOMETOWN').replace('Demo Trail','Route 1').replace('DEMO TRAIL','ROUTE 1');write_if_changed(p,s)
# Scripts are generated below; names and order deliberately explicit.
script=[]
def emit(s):script.append(s+'\n')
def msg(k):return '\tmsgbox Leg_Text_'+k+', MSGBOX_DEFAULT\n'
def seq(*ks):return ''.join(msg(k) for k in ks)
def simple(label,k):emit(label+'::\n\tlock\n\tfaceplayer\n'+msg(k)+'\trelease\n\tend')
def face(actor,d):return f'\tapplymovement {actor}, Leg_Move_Face{d}\n\twaitmovement {actor}\n'
def walk(actor,x,y,vertical=False,d=None):
 r=f'\tsetvar VAR_0x8004, {actor}\n\tsetvar VAR_0x8005, {x}\n\tsetvar VAR_0x8006, {y}\n\tsetvar VAR_0x8007, {int(vertical)}\n\tcallnative LegOneMoveActor\n\twaitmovement {actor}\n'
 return r+(face(actor,d) if d else '')
P='OBJ_EVENT_ID_PLAYER'
emit('LegLab_MapScripts::\n\tmap_script MAP_SCRIPT_ON_TRANSITION, LegLab_OnTransition\n\tmap_script MAP_SCRIPT_ON_FRAME_TABLE, LegLab_OnFrame\n\tmap_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LegLab_OnWarp\n\tmap_script MAP_SCRIPT_ON_RETURN_TO_FIELD, LegLab_BallsLayer\n\t.byte 0\n\nLegLab_OnWarp::\n\tmap_script_2 VAR_TEMP_1, 0, LegLab_BallsInit\n\t.2byte 0\n\nLegLab_BallsInit::\n\tsetvar VAR_TEMP_1, 1\n\nLegLab_BallsLayer::\n\tcallnative LegOneLiftTableBalls\n\tend\n\nLegLab_OnTransition::\n\tsetrespawn HEAL_LOCATION_POC_VILLAGE\n\tend\n\nLegLab_OnFrame::\n\tmap_script_2 VAR_LEG_STAGE, 0, LegLab_Start\n\t.2byte 0')
emit('LegLab_Start::\n\tlockall\n\tsetvar VAR_LEG_STAGE, 1\n\tsetvar VAR_TRAINER_LEVEL, 5\n'+face(P,'Up')+msg('Lab_Welcome')+face(2,'Right')+face(P,'Left')+msg('Lab_Whisper')+msg('Lab_Interrupt')+face(2,'Up')+face(P,'Up')+seq('Lab_Nerves','Lab_Listen')+'\tsetvar VAR_LEG_STAGE, 2\n\tclosemessage\n\treleaseall\n\tend')
emit('LegLab_Table::\n\tlockall\n\tsetvar VAR_LEG_STAGE, 5\n'+face(P,'Up')+seq('Lab_Listening','Lab_Hear','Lab_Table')+'\treleaseall\n\tend')
emit('LegLab_NoExit::\n\tlockall\n'+msg('Lab_FinishChoosing')+'\treleaseall\n\tend')
for i in range(5):
 emit(f'LegLab_Ball{i}::\n\tlockall\n\tsetvar VAR_0x8004, {i}\n\tcallnative LegOneBufferBall\n\tgoto_if_eq VAR_LEG_STAGE, 4, LegLab_BallResting\n\tsetvar VAR_POC_STARTER, '+str(i)+'\n\tcallnative LegOnePreviewStarter\n\tshowmonpic VAR_0x8004, 10, 1\n\tmsgbox Leg_Text_Ball_'+str(i)+', MSGBOX_YESNO\n\tcopyvar VAR_LEG_REPLY, VAR_RESULT\n\thidemonpic\n\tgoto_if_eq VAR_LEG_REPLY, NO, LegLab_BallDeclined\n\tcallnative LegOneGiveStarter\n\tsetflag FLAG_SYS_POKEMON_GET\n\tsetflag FLAG_ADVENTURE_STARTED\n\tsetvar VAR_LEG_STAGE, 3\n\tsetvar VAR_0x8004, 0\n\tcallnative LegOneTakeBall\n'+msg('Lab_Chosen')+'\tsetvar VAR_0x8004, 0\n\tgoto_if_set FLAG_LEG_NICKNAME, LegLab_NameStarter\n\tmsgbox Leg_Text_Lab_Nickname, MSGBOX_YESNO\n\tgoto_if_eq VAR_RESULT, YES, LegLab_NameStarter\n\tgoto LegLab_Selected')
emit('LegLab_BallResting::\n\tmsgbox Leg_BallRemaining, MSGBOX_DEFAULT\n\nLegLab_BallDeclined::\n\treleaseall\n\tend\n\nLegLab_NameStarter::\n\tcall Common_EventScript_NameReceivedPartyMon\n\tgoto LegLab_Selected')
r='LegLab_Selected::\n\tclosemessage\n'+walk(P,7,6)+walk(P,7,9,False,'Up')+msg('Lab_NevChoice')
for role,actor,x,turn,choice in [(2,3,9,'Lab_AstridTurn','Lab_AstridChoice'),(3,4,10,'Lab_EdwulfTurn','Lab_EdwulfChoice'),(1,2,6,'Lab_NevilleTurn','Lab_NevilleChoice')]:
 r+=msg(turn)+'\tclosemessage\n'+walk(actor,x,6)
 if role==1:r+=msg('Lab_NevilleThinking')+'\tclosemessage\n'
 r+=f'\tsetvar VAR_0x8004, {role}\n\tcallnative LegOnePrepareChoice\n\tcallnative LegOneApproachChosenBall\n\twaitmovement {actor}\n\tdelay 16\n\tsetvar VAR_0x8004, {role}\n\tcallnative LegOneTakeBall\n'
 if role==1:r+='\tcallnative LegOneBufferNeville\n'
 r+=msg(choice)+'\tclosemessage\n'+walk(actor,x,6)+walk(actor,x,7,False,'Up')
r+=seq('Lab_Serious','Lab_Introduced','Lab_Before','Lab_Important')+'\tdynmultipush Leg_Reply_Heard, 0\n\tdynmultipush Leg_Reply_Notes, 1\n\tdynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE\n\tgoto_if_eq VAR_RESULT, 1, LegLab_Notes\n'+msg('Lab_Heard')+'\tgoto LegLab_Practice\n\nLegLab_Notes::\n'+msg('Lab_Notes')+'\tgoto LegLab_Practice';emit(r)
emit('LegLab_Practice::\n'+seq('Lab_Fun','Lab_Practice','Lab_Paper','Lab_Safe')+'\tclosemessage\n'+walk(P,5,11,True)+walk(P,5,12,False,'Right')+walk(2,5,13,True)+walk(2,5,14,False,'Right')+walk(3,11,11,True)+walk(3,11,12,False,'Left')+walk(4,11,13,True)+walk(4,11,14,False,'Left')+seq('Lab_ReadyA','Lab_ReadyE','Lab_ReadyN')+'\tclosemessage\n\tcallnative LegOneSetupBattle\n\tspecial SavePlayerParty\n\tsetvar VAR_0x8005, MULTI_BATTLE_2_VS_2\n\tcallnative BattleSetup_StartMultiBattle\n\twaitstate\n\tcopyvar VAR_LEG_REPLY, VAR_RESULT\n\tsetvar VAR_0x8004, FRONTIER_UTIL_FUNC_SAVE_PARTY\n\tspecial CallFrontierUtilFunc\n\tspecial LoadPlayerParty\n\tgoto_if_eq VAR_LEG_REPLY, B_OUTCOME_WON, LegLab_Won\n'+seq('Lab_LoseA','Lab_LoseE','Lab_LoseA2','Lab_LoseN')+'\tgoto LegLab_Feedback\n\nLegLab_Won::\n\tsetflag FLAG_LEG_LAB_WON\n'+seq('Lab_WinN','Lab_WinA')+'\tgoto LegLab_Feedback')
emit('LegLab_Feedback::\n\tclosemessage\n\taddobject 1\n'+walk(1,2,3)+walk(1,2,11,True)+walk(1,7,12,False,'Left')+'\tgoto_if_set FLAG_LEG_LAB_WON, LegLab_WinFeedback\n'+msg('Lab_LoseY')+'\tgoto LegLab_AfterBattle\n\nLegLab_WinFeedback::\n'+msg('Lab_WinY')+'\tgoto LegLab_AfterBattle')
r='LegLab_AfterBattle::\n\tspecial HealPlayerParty\n'+seq('Lab_Rested','Lab_JustAsWell','Lab_Program','Lab_Service','Lab_Opportunities','Lab_VictoryRoad','Lab_Graduation','Lab_HowFar','Lab_Routes')+'\tclosemessage\n'
r+=walk(1,7,11)+walk(1,2,11)+walk(1,2,3,True)+walk(1,8,3,False,'Up')+'\tdelay 24\n'+msg('Lab_Equipment')+'\tclosemessage\n'+walk(1,2,3)+walk(1,2,11,True)+walk(1,6,12,False,'Left')+'\tdelay 24\n\tsetflag FLAG_SYS_POKEDEX_GET\n\tspecial EnableNationalPokedex\n'+msg('DexReceived')+'\tclosemessage\n'
r+=walk(1,10,13)+walk(1,10,12,False,'Right')+'\tdelay 16\n'+walk(1,10,14,False,'Right')+'\tdelay 16\n'+walk(1,6,15)+walk(1,6,14,False,'Left')+'\tdelay 16\n'+walk(1,6,12,False,'Left')+seq('Lab_Dex','Lab_Contributing','Lab_FourTrainers','Lab_Reports','Lab_Automatic','Lab_Invention','Lab_Appreciate','Lab_Goodbyes','Lab_Moving','Lab_GoodbyeHome','Lab_AfterThat')+'\tclosemessage\n'
r+=walk(3,12,12)+walk(3,12,16,True)+walk(3,8,16)+walk(3,8,17)+'\tremoveobject 3\n'+walk(4,11,16,True)+walk(4,8,16)+walk(4,8,17)+'\tremoveobject 4\n'+msg('Lab_MeetNeville')+'\tclosemessage\n'+walk(2,5,16,True)+walk(2,8,16)+walk(2,8,17)+'\tremoveobject 2\n\tsetflag FLAG_LEG_CLASS_LEFT\n\tsetvar VAR_LEG_STAGE, 4\n\treleaseall\n\tend';emit(r)
simple('LegLab_Yew','Lab_YewAgain');simple('LegLab_Classmate','Lab_Table')
for direction in ['Up','Down','Left','Right']:emit('Leg_Move_Face'+direction+'::\n\tface_'+direction.lower()+'\n\tstep_end')

emit('LegHome_MapScripts::\n\t.byte 0\n\nLegHome_Mom::\n\tlock\n\tfaceplayer\n\tspecial HealPlayerParty\n\tgoto_if_set FLAG_LEG_MOM_GIFT, LegHome_Again\n'+msg('Mom_First')+'\tgoto_if_unset FLAG_LEG_LAB_WON, LegHome_HadBattle\n\tdynmultipush Leg_Reply_Won, 0\n\tdynmultipush Leg_Reply_Battled, 1\n\tdynmultistack 1, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE\n\tgoto_if_eq VAR_RESULT, 1, LegHome_HadBattle\n'+msg('Mom_Win')+'\tgoto LegHome_Gifts\n\nLegHome_HadBattle::\n'+msg('Mom_Battle')+'\ngoto LegHome_Gifts\n\nLegHome_Gifts::\n'+msg('Mom_Shoes')+'\tsetflag FLAG_SYS_B_DASH\n'+seq('ShoesReceived','Mom_Map')+'\tgiveitem ITEM_TOWN_MAP\n'+msg('Mom_Farewell')+'\tsetflag FLAG_LEG_MOM_GIFT\n\tsetvar VAR_LEG_FAREWELL, 1\n\trelease\n\tend\n\nLegHome_Again::\n'+msg('Mom_Again')+'\trelease\n\tend')
emit('LegNeville_MapScripts::\n\t.byte 0\n\nLegNeville_Talk::\n\tlock\n\tfaceplayer\n\tgoto_if_set FLAG_LEG_NEV_TALKED, LegNeville_Again\n'+msg('Neville_Home')+'\tdynmultipush Leg_Reply_Knows, 0\n\tdynmultipush Leg_Reply_Food, 1\n\tdynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE\n\tgoto_if_eq VAR_RESULT, 1, LegNeville_Food\n'+msg('Neville_Knows')+'\tgoto LegNeville_Meet\n\nLegNeville_Food::\n'+msg('Neville_Food')+'\ngoto LegNeville_Meet\n\nLegNeville_Meet::\n'+msg('Neville_Meet')+'\tsetflag FLAG_LEG_NEV_TALKED\n\trelease\n\tend\n\nLegNeville_Again::\n'+msg('Neville_Again')+'\trelease\n\tend')
emit('LegNeville_Mother::\n\tlock\n\tfaceplayer\n'+msg('NevMom')+'\tgoto_if_set FLAG_LEG_NEVILLE_LEFT, LegNeville_MotherEnd\n'+seq('NevOnce','NevTwice')+'\nLegNeville_MotherEnd::\n'+msg('NevMom_End')+'\trelease\n\tend')
emit('LegAstrid_MapScripts::\n\t.byte 0');simple('LegAstrid_Parent','AstridParent')
emit('LegEdwulf_MapScripts::\n\t.byte 0\n\nLegEdwulf_Parent::\n\tlock\n\tfaceplayer\n\tgoto_if_set FLAG_LEG_ED_TALKED, LegEdwulf_Repeat\n'+seq('EdParents','EdParents2')+'\tdynmultipush Leg_Reply_No, 0\n\tdynmultipush Leg_Reply_Yes, 1\n\tdynmultistack 2, 0, TRUE, 2, FALSE, 0, DYN_MULTICHOICE_CB_NONE\n\tgoto_if_eq VAR_RESULT, 1, LegEdwulf_Yes\n'+msg('EdParents_No')+'\tgoto LegEdwulf_End\n\nLegEdwulf_Yes::\n'+msg('EdParents_Yes')+'\ngoto LegEdwulf_End\n\nLegEdwulf_End::\n'+msg('EdParents_End')+'\tsetflag FLAG_LEG_ED_TALKED\n\trelease\n\tend\n\nLegEdwulf_Repeat::\n'+msg('EdParents_Again')+'\trelease\n\tend');simple('LegEdwulf_Again','EdParents_Again')
emit('LegOldMan_MapScripts::\n\t.byte 0\n\nLegOldMan_Talk::\n\tlock\n\tfaceplayer\n\tgoto_if_set FLAG_LEG_OLD_TALKED, LegOldMan_Again\n'+msg('OldMan')+'\tsetflag FLAG_LEG_OLD_TALKED\n\trelease\n\tend\n\nLegOldMan_Again::\n'+msg('OldMan_Again')+'\trelease\n\tend')
for n in ['Resident','Worker','SetMoves','Child','Guide','Boundary']:simple('Leg_'+n,n)
emit('Leg_FastLevel::\n\tlock\n\tfaceplayer\n'+msg('FastLevel')+'\tgoto_if_set FLAG_LEG_FAST_LEVEL, Leg_FastLevelEnd\n'+msg('FastLevel_Off')+'\nLeg_FastLevelEnd::\n\trelease\n\tend')
for n in ['Mom','Neville','Astrid','Edwulf','OldMan','Lab']:
 label='LegHome' if n=='Mom' else 'Leg'+n
 emit('Leg_Sign_'+label+'::\n\tmsgbox Leg_Text_Sign_'+n+', MSGBOX_SIGN\n\tend')
emit('Leg_NeedMom::\n\tlockall\n'+msg('NeedMom')+'\tclosemessage\n\tapplymovement OBJ_EVENT_ID_PLAYER, Leg_Move_Down\n\twaitmovement 0\n\treleaseall\n\tend')
emit('Leg_Complete::\n\tlockall\n\tsetvar VAR_LEG_COMPLETE, 1\n\tsetflag FLAG_LEG_NEVILLE_LEFT\n'+msg('Complete')+'\treleaseall\n\tend')
emit('Leg_Preferences::\n\tlockall\n\tcall Leg_PrefsSetup\n\treleaseall\n\tend\n\nLeg_PrefsSetup::\n'+msg('Prefs')+'\tmsgbox Leg_Text_Prefs_Nick, MSGBOX_YESNO\n\tclearflag FLAG_LEG_NICKNAME\n\tgoto_if_eq VAR_RESULT, NO, Leg_PrefsFast\n\tsetflag FLAG_LEG_NICKNAME\n\nLeg_PrefsFast::\n\tmsgbox Leg_Text_Prefs_Fast, MSGBOX_YESNO\n\tclearflag FLAG_LEG_FAST_LEVEL\n\tgoto_if_eq VAR_RESULT, NO, Leg_PrefsMoves\n\tsetflag FLAG_LEG_FAST_LEVEL\n\nLeg_PrefsMoves::\n\tmsgbox Leg_Text_Prefs_Moves, MSGBOX_YESNO\n\tclearflag FLAG_LEG_SET_MOVES\n\tgoto_if_eq VAR_RESULT, NO, Leg_PrefsDone\n\tsetflag FLAG_LEG_SET_MOVES\n\nLeg_PrefsDone::\n'+msg('Prefs_Done')+'\treturn')
# Compact movement, no movement through furniture or another actor.
for n,steps in {'Neville':['walk_down','walk_left','face_right'],'Astrid':['walk_right','face_left'],'Edwulf':['walk_down','walk_right','face_left'],'Player':['walk_down','face_right'],'ExitA':['walk_down']*4+['walk_left']*2+['walk_down'],'ExitE':['walk_left']*2+['walk_down']*4,'ExitN':['walk_right']*2+['walk_down']*4,'Down':['walk_down']}.items():
 emit('Leg_Move_'+n+':\n'+''.join('\t'+s+'\n' for s in steps)+'\tstep_end')
for i,n in enumerate(['Vulpix','Psyduck','Phanpy','Crabrawler','Deerling']):emit(f'Leg_Option_{i}:\n\t.string "{n}$"')
for key,s in {'Heard':'We heard her.','Notes':'You two can take notes for us.','Won':'We won our first battle.','Battled':'We had our first battle.','Knows':'She knows you.','Food':'Any food in there?','No':"They didn't say.",'Yes':"I'm sure we can."}.items():emit(f'Leg_Reply_{key}:\n\t.string "{s}$"')
emit('Leg_BallRemaining:\n\t.string "A {STR_VAR_1} is resting inside.$"')
emit('Leg_TownMap::\n\tlockall\n\tcallnative LegOneShowTownMap\n\twaitstate\n\treleaseall\n\tend')
put('data/our-game/events.inc',''.join(script))
put('data/maps/PocVillage/scripts.inc','PocVillage_MapScripts::\n\tmap_script MAP_SCRIPT_ON_TRANSITION, PocVillage_OnTransition\n\t.byte 0\n\nPocVillage_OnTransition::\n\tsetrespawn HEAL_LOCATION_POC_VILLAGE\n\tend\n')
put('data/maps/PocTrail/scripts.inc','PocTrail_MapScripts::\n\t.byte 0\n')
for name,_,_ in houses:put('data/maps/'+name+'/scripts.inc','@ Scripts are maintained in data/our-game/events.inc\n')
p=ROOT/'data/event_scripts.s';s=p.read_text()
if 'data/our-game/events.inc' not in s:s+='\n\t.include "data/our-game/events.inc"\n\t.include "data/our-game/text.inc"\n'
write_if_changed(p,s)
print('Generated leg-one maps, dialogue, events, and canonical dialogue log.')

emit('LegHomeUpstairs_MapScripts::\n\t.byte 0');simple('LegHome_PC','Home_PC')
emit('LegHome_Bed::\n\tlockall\n'+msg('Home_Bed')+'\tspecial HealPlayerParty\n\treleaseall\n\tend')
put('data/our-game/events.inc',''.join(script))
