#include "april-ann.h" // includes all APRIL-ANN headers

using namespace AprilMath::MatrixExt::BLAS;
using namespace AprilMath::MatrixExt::Initializers;

using AprilUtils::LuaTable;
using AprilUtils::SharedPtr;
using Basics::MatrixFloat;

int get(lua_State *L) {
  SharedPtr<MatrixFloat> m1 = new MatrixFloat(2, 10, 20);
  SharedPtr<MatrixFloat> m2 = new MatrixFloat(2, 20, 10);
  matFill(m1.get(), 20.0f);
  matFill(m2.get(), 10.0f);
  SharedPtr<MatrixFloat> m3 = new MatrixFloat(2, 10, 10);
  matGemm(m3.get(), CblasNoTrans, CblasNoTrans,
          1.0f, m1.get(), m2.get(), 0.0f);
  // using LuaTable you can push APRIL-ANN objects in Lua stack (be careful, not
  // all objects can be pushed)
  LuaTable::pushInto(L, m3.get());
  return 1;
}

extern "C" {
  int luaopen_example(lua_State *L) {
    static const luaL_Reg funcs[] = {
      {"get", get},
      {NULL, NULL}
    };
    luaL_requiref(L, "aprilann", luaopen_aprilann, 1);
    luaL_newlib(L, funcs);
    return 1;
  }
}
