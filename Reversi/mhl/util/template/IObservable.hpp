#ifndef MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_
#define MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_



namespace mhl {

    // 前方宣言
    class Subject;

    // オブザーバーインターフェースクラス
    class IObservable {
    public:

        virtual ~IObservable() {
        }

        virtual void Update(Subject& subject) = 0;

    };

}

#endif  // MH_LIBRARY_UTIL_TEMPLATE_IOBSERVABLE_HPP_
