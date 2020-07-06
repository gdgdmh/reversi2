#ifndef MH_LIBRABY_TEST_UNITTESTEXECUTELIST_H_
#define MH_LIBRABY_TEST_UNITTESTEXECUTELIST_H_

#include <list>
#include <memory>

#include "UnitTestBase.hpp"

namespace mhl {

// 単体テスト実行リストクラス
class UnitTestExecuteList {
 public:
  UnitTestExecuteList();

  virtual ~UnitTestExecuteList();

  void Add(const std::shared_ptr<UnitTestBase>& unit_test);

  bool Execute();

 protected:
  std::list<std::shared_ptr<UnitTestBase> > unit_test_list;
};

}  // namespace mhl

#endif  // MH_LIBRABY_TEST_UNITTESTEXECUTELIST_H_
