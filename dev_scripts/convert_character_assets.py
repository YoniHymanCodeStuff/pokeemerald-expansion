"""Convert approved reference sheets to native 16-colour GBA asset layouts."""
from pathlib import Path
from PIL import Image
R=Path(__file__).resolve().parents[1];S=R/'graphics/our_game/references';O=R/'graphics/our_game/characters';O.mkdir(parents=True,exist_ok=True)
def cut(im):
 im=im.convert('RGBA');alpha=im.getchannel('A').point(lambda v:255 if v>=128 else 0);im.putalpha(alpha);return im.crop(im.getbbox())
def indexed(im,path):
 alpha=im.getchannel('A');rgb=im.convert('RGB');q=rgb.quantize(colors=15,method=Image.Quantize.MEDIANCUT,dither=Image.Dither.NONE);o=Image.new('P',im.size);o.putpalette([0,0,0]+q.getpalette()[:45]+[0]*720);o.putdata([v+1 if a else 0 for v,a in zip(q.getdata(),alpha.getdata())]);o.save(path,transparency=0)
for name in ['yew','astrid','edwulf','neville']:
 im=cut(Image.open(S/(name+'.png')));k=min(62/im.width,62/im.height);im=im.resize((round(im.width*k),round(im.height*k)),Image.Resampling.NEAREST);o=Image.new('RGBA',(64,64));o.alpha_composite(im,((64-im.width)//2,64-im.height));indexed(o,O/(name+'-front.png'))
 im=Image.open(S/(name+'-overworld.png')).convert('RGBA');im.putalpha(im.getchannel('A').point(lambda v:255 if v>=128 else 0))
 # Locate inter-row gaps rather than assuming generated sheets have exact thirds.
 density=[sum(1 for a in im.getchannel('A').crop((0,y,im.width,y+1)).getdata() if a) for y in range(im.height)]
 ys=[0]+[min(range(int(im.height*(f-.075)),int(im.height*(f+.075))),key=lambda y:density[y]) for f in [1/3,2/3]]+[im.height]
 cells=[cut(im.crop((round(c*im.width/3),ys[r],round((c+1)*im.width/3),ys[r+1]))) for r in range(3) for c in range(3)]
 k=min(min(16/c.width,30/c.height) for c in cells);o=Image.new('RGBA',(144,32))
 for i,j in enumerate([0,3,6,1,2,4,5,7,8]):
  c=cells[j];c=c.resize((max(1,round(c.width*k)),max(1,round(c.height*k))),Image.Resampling.NEAREST);o.alpha_composite(c,(i*16+(16-c.width)//2,32-c.height))
 indexed(o,O/(name+'-overworld.png'))
im=cut(Image.open(S/'neville-back.png'));k=min(64/im.width,64/im.height);im=im.resize((round(im.width*k),round(im.height*k)),Image.Resampling.NEAREST);o=Image.new('RGBA',(64,64));o.alpha_composite(im,((64-im.width)//2,64-im.height));indexed(o,O/'neville-back.png')
