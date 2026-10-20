"""Validate branch data and map connections before compiling the ROM."""
import json,re,struct,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
def load(p):return json.loads((ROOT/p).read_text())
class LegOneContent(unittest.TestCase):
 def test_every_starter_assignment_is_distinct(self):
  s=(ROOT/'src/leg_one.c').read_text()
  rows=re.search(r'sStarterAssignments\[5\]\[4\] = \{(.*?)\};',s).group(1)
  rows=[list(map(int,re.findall(r'\d+',r))) for r in re.findall(r'\{([^}]+)\}',rows)]
  self.assertEqual(len(rows),5)
  for i,row in enumerate(rows):self.assertEqual(row[0],i);self.assertEqual(len(set(row)),4);self.assertTrue(all(0<=x<5 for x in row))
 def test_all_warps_have_reverse_destinations(self):
  groups=load('data/maps/map_groups.json')['gMapGroup_Poc']
  maps={load(f'data/maps/{n}/map.json')['id']:load(f'data/maps/{n}/map.json') for n in groups}
  for mid,m in maps.items():
   if mid=='MAP_POC_CABIN':continue # Retained legacy map is not reachable.
   for warp in m['warp_events']:
    dest=maps[warp['dest_map']]
    self.assertLess(int(warp['dest_warp_id']),len(dest['warp_events']))
    self.assertEqual(dest['warp_events'][int(warp['dest_warp_id'])]['dest_map'],mid)
 def test_layout_sizes_and_npc_positions(self):
  layouts={x['id']:x for x in load('data/layouts/layouts.json')['layouts']}
  for n in load('data/maps/map_groups.json')['gMapGroup_Poc']:
   if n=='PocCabin':continue # Legacy, unconnected POC interior.
   m=load(f'data/maps/{n}/map.json');l=layouts[m['layout']]
   raw=(ROOT/l['blockdata_filepath']).read_bytes();self.assertEqual(len(raw),2*l['width']*l['height'])
   tiles=struct.unpack('<'+'H'*(len(raw)//2),raw)
   for o in m['object_events']:
    self.assertLess(o['x'],l['width']);self.assertLess(o['y'],l['height'])
    if o['graphics_id'] != 'OBJ_EVENT_GFX_ITEM_BALL':self.assertEqual(tiles[o['y']*l['width']+o['x']]&0xc00,0,f'{n} NPC on blocked tile: {o}')
 def test_departed_rivals_absent_from_houses(self):
  for n in ['LegAstrid','LegEdwulf']:
   self.assertFalse(any(o['script']=='LegLab_Classmate' for o in load(f'data/maps/{n}/map.json')['object_events']))
 def test_all_script_texts_resolve(self):
  ev=(ROOT/'data/our-game/events.inc').read_text()
  refs=set(re.findall(r'Leg_Text_[A-Za-z0-9_]+',ev))
  defs=set(re.findall(r'(Leg_Text_[A-Za-z0-9_]+)::',(ROOT/'data/our-game/text.inc').read_text()))
  self.assertFalse(refs-defs,refs-defs)
 def test_old_man_and_board_edits_preserved(self):
  d=load('data/our-game/dialogue.json')
  self.assertIn('prayer it held till morning',d['OldMan'])
  self.assertIn('Doors wide open',d['OldMan'])
  self.assertIn('Who is interrupting me?',d['Lab_Interrupt'])
  self.assertIn('supreme commander',d['Lab_NevilleChoice'])
  self.assertIn('custom moveset for important battles',d['SetMoves'])
 def test_individual_starter_balls_and_stages(self):
  m=load('data/maps/LegLab/map.json')
  balls=[o for o in m['object_events'] if o['graphics_id']=='OBJ_EVENT_GFX_ITEM_BALL']
  self.assertEqual([o['x'] for o in balls],[4,6,8,10,12])
  self.assertTrue(all(o['y']==5 for o in balls))
  ev=(ROOT/'data/our-game/events.inc').read_text()
  self.assertIn('setvar VAR_LEG_STAGE, 2\n\tclosemessage\n\treleaseall',ev)
  self.assertIn('LegLab_Table::',ev)
  for i in range(5):
   block=ev.split(f'LegLab_Ball{i}::')[1].split('\n\n')[0]
   self.assertIn('showmonpic',block)
   self.assertIn(f'Leg_Text_Ball_{i}',block)
  self.assertNotIn('dynmultipush Leg_Option_',ev)
 def test_two_storey_home_and_parent_names(self):
  home=load('data/maps/LegHome/map.json');up=load('data/maps/LegHomeUpstairs/map.json')
  self.assertEqual(home['warp_events'][2]['dest_map'],up['id'])
  self.assertEqual(up['warp_events'][0]['dest_warp_id'],'2')
  d=load('data/our-game/dialogue.json')
  self.assertIn('ASTRID\'S MOM:',d['AstridParent'])
  self.assertIn('EDWULF\'S MOM:',d['EdParents'])
  self.assertNotIn('put your things by the door',d['Mom_Shoes'])
 def test_native_custom_assets(self):
  from PIL import Image
  for n in ['yew','astrid','edwulf','neville']:
   for suffix,size in [('front',(64,64)),('overworld',(144,32))]:
    im=Image.open(ROOT/f'graphics/our_game/characters/{n}-{suffix}.png')
    self.assertEqual(im.size,size);self.assertEqual(im.mode,'P');self.assertLessEqual(len(im.getcolors()),16)
if __name__=='__main__':unittest.main()
