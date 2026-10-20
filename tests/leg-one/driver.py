"""Small headless mGBA controller for repeatable opening playtests."""
import ctypes as C,json,subprocess,sys,os
from pathlib import Path
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
lib=C.CDLL(os.environ.get('LEG_ONE_EMULATOR_LIBRARY',str(ROOT.parent/'emulator.so')))
lib.emu_init.argtypes=[C.c_char_p];lib.emu_init.restype=C.c_int
lib.emu_step.argtypes=[C.c_uint,C.c_uint];lib.emu_read.argtypes=[C.c_uint,C.c_uint];lib.emu_read.restype=C.c_uint
lib.emu_write.argtypes=[C.c_uint,C.c_uint,C.c_uint];lib.emu_pixels.restype=C.c_void_p
lib.emu_battery.argtypes=[C.c_char_p];lib.emu_load_battery.argtypes=[C.c_char_p]
lib.emu_state_save.argtypes=[C.c_char_p];lib.emu_state_load.argtypes=[C.c_char_p]
assert lib.emu_init(str(ROOT/'pokeemerald.gba').encode())
syms={}
nm=os.environ.get('ARM_NM','arm-none-eabi-nm')
for line in subprocess.check_output([str(nm),'-n',str(ROOT/'pokeemerald.elf')],text=True).splitlines():
 p=line.split()
 if len(p)==3:
  try:syms[p[2]]=int(p[0],16)
  except ValueError:pass
addrnames={v:k for k,v in syms.items()}
OUT=ROOT.parent/'playtest';OUT.mkdir(exist_ok=True)
def read(a,n=4):return lib.emu_read(a,n)
chars={0:' ',0xAD:'.',0xAE:'-',0xB8:',',0xB4:"'",0xAB:'!',0xAC:'?',0xF0:':'}
chars.update({0xBB+i:chr(65+i) for i in range(26)});chars.update({0xD5+i:chr(97+i) for i in range(26)});chars.update({0xA1+i:str(i) for i in range(10)})
def currenttext():
 a=syms['gStringVar4'];v=[]
 for i in range(1000):
  b=read(a+i,1)
  if b==255:break
  v.append(chars.get(b,' '))
 return ''.join(v)
def tasks():
 a=syms['gTasks'];out=[]
 for i in range(16):
  if read(a+i*40+4,1):
   f=read(a+i*40)&~1
   out.append([i,addrnames.get(f,hex(f)),[read(a+i*40+8+j*2,2) for j in range(16)]])
 return out
def handle(q):
  for op in q.get('ops',[]):
   cmd=op[0]
   if cmd=='step':lib.emu_step(op[1],op[2])
   if cmd=='press':
    lib.emu_step(op[1],op[2] if len(op)>2 else 1);lib.emu_step(0,op[3] if len(op)>3 else 20)
   if cmd=='advance':
    for _ in range(op[1]):lib.emu_step(1,2);lib.emu_step(0,18)
   if cmd=='until':
    for _ in range(op[2]):
     if any(op[1] in t[1] for t in tasks()):break
     lib.emu_step(1,2);lib.emu_step(0,18)
   if cmd in ['untiltext','untilstage']:
    for _ in range(op[2]):
     sb=read(syms['gSaveBlock1Ptr'])
     if cmd=='untiltext' and op[1] in currenttext():break
     if cmd=='untilstage' and 0x02000000<=sb<0x02040000 and read(sb+5020+0xfa*2,2)==op[1]:break
     lib.emu_step(1,4);lib.emu_step(0,16)
   if cmd=='write':lib.emu_write(syms.get(op[1],op[1]) if isinstance(op[1],str) else op[1],op[2],op[3] if len(op)>3 else 4)
   if cmd=='battery':lib.emu_battery(str(OUT/op[1]).encode())
   if cmd=='loadbattery':lib.emu_load_battery(str(OUT/op[1]).encode())
   if cmd=='reset':lib.emu_reset()
   if cmd=='go':
    for _ in range(100):
     a=syms['gObjectEvents']+36*read(syms['gPlayerAvatar']+5,1)+16
     x,y=read(a,2)-7,read(a+2,2)-7
     if [x,y]==op[1:3]:break
     k=16 if x<op[1] else 32 if x>op[1] else 128 if y<op[2] else 64
     lib.emu_step(k,16);lib.emu_step(0,3)
   if cmd=='save':lib.emu_state_save(str(OUT/op[1]).encode())
   if cmd=='load':lib.emu_state_load(str(OUT/op[1]).encode())
  a=syms['gObjectEvents']+36*read(syms['gPlayerAvatar']+5,1)+16
  sb=read(syms['gSaveBlock1Ptr'])
  result={'tasks':tasks(),'pos':[read(a,2)-7,read(a+2,2)-7],'stage':read(sb+5020+0xfa*2,2),'farewell':read(sb+5020+0xf8*2,2),'complete':read(sb+5020+0xf9*2,2)}
  if q.get('text'):result['text']=currenttext()
  if q.get('objects'):
   result['objects']=[]
   for i in range(16):
    a=syms['gObjectEvents']+36*i
    if read(a,1)&1:result['objects'].append({'id':read(a+8,1),'pos':[read(a+16,2)-7,read(a+18,2)-7],'face':read(a+24,1)&15})
  if 'read' in q:result['read']=[read(syms.get(a,a) if isinstance(a,str) else a,n) for a,n in q['read']]
  if 'shot' in q:
   arr=C.string_at(lib.emu_pixels(),256*160*4)
   im=Image.frombytes('RGBA',(256,160),arr).crop((0,0,240,160)).convert('RGB');im.save(OUT/q['shot']);result['image']=str(OUT/q['shot'])
  if q.get('symbols'):result['symbols']={k:syms[k] for k in q['symbols'] if k in syms}
  return result

print("Ready",flush=True)
for line in sys.stdin:
 try:print(json.dumps(handle(json.loads(line))),flush=True)
 except Exception as e:print(json.dumps({"error":str(e)}),flush=True)
