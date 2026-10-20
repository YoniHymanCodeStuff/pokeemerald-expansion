#include <mgba/flags.h>
#include <mgba/core/core.h>
#include <mgba/core/log.h>
#include <mgba/core/config.h>
#include <mgba-util/vfs.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
static struct mCore *core;
static void quietlog(struct mLogger *l, int c, enum mLogLevel level, const char *f, va_list args) {}
static struct mLogger logger = {.log = quietlog};
static color_t pixels[256 * 256];
int emu_init(const char *path) {
 mLogSetDefaultLogger(&logger);
 core = mCoreFind(path); if(!core || !core->init(core)) return 0;
 mCoreInitConfig(core, NULL);
 core->opts.useBios = false; core->opts.skipBios = true;
 core->setVideoBuffer(core, pixels, 256);
 if(!mCoreLoadFile(core, path)) return 0;
 core->reset(core); return 1;
}
void emu_step(unsigned keys,unsigned frames){core->setKeys(core,keys); for(unsigned i=0;i<frames;i++)core->runFrame(core);}
uint32_t emu_read(unsigned a,unsigned n){return n==1?core->busRead8(core,a):n==2?core->busRead16(core,a):core->busRead32(core,a);}
void emu_write(unsigned a,unsigned v,unsigned n){if(n==1)core->busWrite8(core,a,v);else if(n==2)core->busWrite16(core,a,v);else core->busWrite32(core,a,v);}
void *emu_pixels(void){return pixels;}
int emu_state_save(const char *p){struct VFile *v=VFileOpen(p,O_CREAT|O_RDWR|O_TRUNC);if(!v)return 0;bool ok=mCoreSaveStateNamed(core,v,0);v->close(v);return ok;}
int emu_state_load(const char *p){struct VFile *v=VFileOpen(p,O_RDONLY);if(!v)return 0;bool ok=mCoreLoadStateNamed(core,v,0);v->close(v);return ok;}

void emu_reset(void){core->reset(core);}
int emu_battery(const char *p){void *data;size_t n=core->savedataClone(core,&data);FILE *f=fopen(p,"wb");if(!f)return 0;size_t w=fwrite(data,1,n,f);fclose(f);free(data);return w==n;}
int emu_load_battery(const char *p){struct VFile *f=VFileOpen(p,O_RDWR);return f&&core->loadSave(core,f);}
