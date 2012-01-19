// Copyright © 2011, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __COREINTERFACES_H
#define __COREINTERFACES_H

#include "store.hh"
#include "smallint.hh"
#include "emulate.hh"
#include "callables.hh"
#include "variables.hh"
#include "boolean.hh"

#include <iostream>

struct Equatable {
  Equatable(Node& self) : self(Reference::dereference(self)) {}

  BuiltinResult equals(VM vm, UnstableNode* right, UnstableNode* result) {
    if (self.type == SmallInt::type) {
      return IMPL(BuiltinResult, SmallInt, equals,
                  &self, vm, right, result);
    } else {
      // TODO == of non-SmallInt
      cout << self.type->getName() << " == (right) not implemented yet" << endl;
      result->make<Boolean>(vm, false);
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

struct BuiltinCallable {
  BuiltinCallable(Node& self) : self(Reference::dereference(self)) {};

  BuiltinResult callBuiltin(VM vm, int argc, UnstableNode* args[]) {
    if (self.type == BuiltinProcedure::type) {
      return IMPL(BuiltinResult, BuiltinProcedure, callBuiltin,
                  &self, vm, argc, args);
    } else {
      // TODO call non-builtin
      cout << "BuiltinProcedure expected but " << self.type->getName();
      cout << " found" << endl;
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

struct Callable {
  Callable(Node& self) : self(Reference::dereference(self)) {};

  BuiltinResult getCallInfo(VM vm, int* arity, CodeArea** body,
    StaticArray<StableNode>** Gs) {
    if (self.type == Abstraction::type) {
      return IMPL(BuiltinResult, Abstraction, getCallInfo,
                  &self, vm, arity, body, Gs);
    } else {
      // TODO call non-abstraction
      cout << "Abstraction expected but " << self.type->getName();
      cout << " found" << endl;
      *arity = 0;
      *body = nullptr;
      *Gs = nullptr;
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

struct Addable {
  Addable(Node& self) : self(Reference::dereference(self)) {};

  BuiltinResult add(VM vm, UnstableNode* right, UnstableNode* result) {
    if (self.type == SmallInt::type) {
      return IMPL(BuiltinResult, SmallInt, add,
                  &self, vm, right, result);
    } else {
      // TODO add non-SmallInt
      cout << "SmallInt expected but " << self.type->getName();
      cout << " found" << endl;
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

struct IntegerValue {
  IntegerValue(Node& self) : self(Reference::dereference(self)) {}

  BuiltinResult equalsInteger(VM vm, nativeint right, bool* result) {
    if (self.type == SmallInt::type) {
      return IMPL(BuiltinResult, SmallInt, equalsInteger,
                  &self, vm, right, result);
    } else {
      // TODO equalsInteger on a non-SmallInt
      *result = false;
      return BuiltinResultContinue;
    }
  }

  BuiltinResult addValue(VM vm, nativeint b, UnstableNode* result) {
    if (self.type == SmallInt::type) {
      return IMPL(BuiltinResult, SmallInt, addValue,
                  &self, vm, b, result);
    } else {
      // TODO addValue on a non-SmallInt
      result->make<SmallInt>(vm, 0);
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

struct BooleanValue {
  BooleanValue(Node& self) : self(Reference::dereference(self)) {}

  BuiltinResult valueOrNotBool(VM vm, BoolOrNotBool* result) {
    if (self.type == Boolean::type) {
      return IMPL(BuiltinResult, Boolean, valueOrNotBool,
                  &self, vm, result);
    } else {
      // TODO valueOrNotBool on a non-Boolean
      *result = bNotBool;
      return BuiltinResultContinue;
    }
  }
private:
  Node& self;
};

#endif // __COREINTERFACES_H
