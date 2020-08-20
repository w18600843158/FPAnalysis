#ifndef FPINTERFACE_H
#define FPINTERFACE_H

#include "communicator.h"
#include <functional>
#include "target.h"

const std::vector<std::function<double(double)>> simpleFuncList = {
    foo,
};

class FloatingPointFunction {
public:
    virtual void call(double x) = 0;
    virtual double getResult() = 0;
    virtual double callAndGetResult(double x) = 0;
    virtual bool isSuccess() = 0;
    std::vector<InstInfo> getInstInfoList() {
        return comm.getInstInfoList();
    }
    FloatingPointFunction() : comm( Communicator::getInstance() ) {
        comm.initComm();
    }
protected:
    double in, out;
    int status;
    Communicator &comm;
};


class SimpleFunction : public FloatingPointFunction {
public:
    SimpleFunction(int index) {
        if (index < 0 || index >= simpleFuncList.size()) {
            std::cout << "Invalid index in [SimpleFunction]: " << index << '\n';
            funcRef = simpleFuncList[0];
            return;
        }
        funcRef = simpleFuncList[index];
    }
    void call(double x) {
        comm.clear();
        in = x;
        out = funcRef(x);
        if (std::isnan(out)) {
            status = -1;
        }
        else {
            status = 0;
        }
    }

    double callAndGetResult(double x) {
        call(x);
        return out;
    }

    double getResult() { return out; }
    bool isSuccess() { return (status == 0); }

private:
    std::function<double(double)> funcRef; // std::function 的实例能存储、复制及调用任何可调用 (Callable)

};

#endif