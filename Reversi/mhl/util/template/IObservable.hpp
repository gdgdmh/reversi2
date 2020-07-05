#ifndef MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_
#define MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_



namespace mhl {

    // �O���錾
    class Subject;

    // �I�u�U�[�o�[�C���^�[�t�F�[�X�N���X
    class IObservable {
    public:

        virtual ~IObservable() {
        }

        virtual void Update(Subject& subject) = 0;

    };

}

#endif  // MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_
