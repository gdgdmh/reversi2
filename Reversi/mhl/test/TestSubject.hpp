#ifndef TEST_TESTSUBJECT_HPP_
#define TEST_TESTSUBJECT_HPP_

#include <memory>
#include "UnitTestBase.hpp"
#include "../util/template/IExecuteMethod.hpp"
#include "../util/template/IObservable.hpp"
#include "../util/template/Subject.hpp"

namespace test {

    // �e�X�g�̂��߂̃N���X
    class TestObserver : public mhl::IObservable {
    public:
        TestObserver() : value(0) {
        }

        void Update(mhl::Subject& subject) {
            value = 1;
        }

        int Get() const {
            return value;
        }

    private:
        int value;
    };


    // ���\�b�h���s�e�X�g�N���X
    class TestSubject : public mhl::UnitTestBase {
    public:
        /**
         * �R���X�g���N�^
         */
        TestSubject(std::shared_ptr<mhl::IOutputConsole> output_console);

        /**
         * �f�X�g���N�^
         */
        virtual ~TestSubject();

        void ExecuteUnitTest();
    };

}

#endif  // TEST_TESTSUBJECT_HPP_
