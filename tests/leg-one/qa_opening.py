"""Replay the five starter choices from a same-build table checkpoint."""
import runpy,json
from pathlib import Path
D=runpy.run_path(str(Path(__file__).with_name('driver.py')))
h=D['handle'];results=[]
h({'ops':[['step',0,400],['press',8,4,240],['press',8,4,200],['press',8,4,120],['press',8,4,180],['press',1,4,250],['untilstage',2,900],['step',0,40],['go',7,6],['untilstage',5,100],['advance',80],['save','final-table.state']]})
for i,name in enumerate(['VULPIX','PSYDUCK','PHANPY','CRABRAWLER','DEERLING']):
 h({'ops':[['load','final-table.state'],['step',0,40],['go',4+2*i,6],['step',0,40],['press',64,4,30],['press',1,4,100],['until','Task_HandleYesNoInput',120]]})
 r=h({'text':True});assert name in r['text'],r
 if i==0:
  h({'ops':[['press',128,4,20],['press',1,4,60]]})
  r=h({'objects':True});assert r['stage']==5 and len([o for o in r['objects'] if 5<=o['id']<=9])==5,r
  h({'ops':[['press',64,4,30],['press',1,4,100],['until','Task_HandleYesNoInput',120]]})
 h({'ops':[['press',1,4,20],['untiltext','nickname',150],['until','Task_HandleYesNoInput',100],['press',128,4,20],['press',1,4,20],['untiltext','Ready?',650],['step',0,80]]})
 r=h({'objects':True,'text':True,'shot':'starter-'+name.lower()+'.png'})
 assert r['stage']==3 and r['pos']==[5,12] and 'Ready?' in r['text'],r
 actors={o['id']:o['pos'] for o in r['objects']}
 assert actors[2]==[5,14] and actors[3]==[11,12] and actors[4]==[11,14],r
 assert len([o for o in r['objects'] if 5<=o['id']<=9])==1,r
 results.append({'starter':name,'practice_positions':'pass','remaining_balls':1})
 print(json.dumps(results[-1]),flush=True)
h({'ops':[['save','final-deerling-ready.state']]})
(Path(__file__).resolve().parents[3]/'playtest'/'starter-results.json').write_text(json.dumps(results,indent=2))
