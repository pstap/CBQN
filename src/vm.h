#pragma once
typedef struct Comp Comp;
typedef struct BlBlocks BlBlocks;
typedef struct Block Block;
typedef struct Body Body;
typedef struct Scope Scope;
typedef struct ScopeExt ScopeExt;

typedef struct Comp {
  struct Value;
  B bc;
  B src;
  B indices;
  HArr* objs;
  u32 blockAm;
} Comp;

struct BlBlocks {
  struct Value;
  u32 am;
  Block* a[];
};

struct Block {
  struct Value;
  bool imm;
  u8 ty;
  Body* body;
};

typedef struct NSDesc NSDesc;
struct Body {
  struct Value;
  Comp* comp;
  BlBlocks* blocks;
  // B* objs;
  i32* bc; // pointer in comp->bc
  u32 maxStack;
  u16 maxPSC;
  u16 varAm;
  u32 endStack;
  NSDesc* nsDesc;
  i32 varIDs[];
};

struct ScopeExt {
  u16 varAm;
  B vars[];
};

struct Scope {
  struct Value;
  Scope* psc;
  Body* body;
  u16 varAm;
  ScopeExt* ext;
  B vars[];
};


Block* compile(B bcq, B objs, B blocksq, B indices, B tokenInfo, B src, Scope* sc);


typedef struct Env {
  Scope* sc;
  union { i32* bcL; i32 bcV; };
} Env;

void vm_pst(Env* s, Env* e);
void vm_pstLive();

typedef struct FunBlock { struct Fun; Scope* sc; Block* bl; } FunBlock;
typedef struct Md1Block { struct Md1; Scope* sc; Block* bl; } Md1Block;
typedef struct Md2Block { struct Md2; Scope* sc; Block* bl; } Md2Block;
// all don't consume anything
B m_funBlock(Block* bl, Scope* psc); // may return evaluated result, whatever
B m_md1Block(Block* bl, Scope* psc);
B m_md2Block(Block* bl, Scope* psc);






extern Env* envCurr;
extern Env* envStart;
extern Env* envEnd;

static inline void pushEnv(Scope* sc, i32* bc) {
  if (envCurr==envEnd) thrM("Stack overflow");
  envCurr->sc = sc;
  envCurr->bcL = bc;
  envCurr++;
}
static inline void popEnv() {
  assert(envCurr>envStart);
  envCurr--;
}
