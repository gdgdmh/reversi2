#ifndef MHL_TEST_UNITTESTEXECUTELIST_HPP_
#define MHL_TEST_UNITTESTEXECUTELIST_HPP_

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

#endif  // MHL_TEST_UNITTESTEXECUTELIST_HPP_
