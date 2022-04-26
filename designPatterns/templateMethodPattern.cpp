#include<iostream>

/**
 * Abstract Class định nghĩa 1 phương thức template chứa 1 bộ khung xương của 1 thuật toán,
 * bao gồm các lời gọi hàm tới (luôn luôn) các hàm nguyên thủy trừu tượng.
 *
 * Các subclasses nên implement các hàm trừu tượng này, nhưng để phương thức template
 * nguyên vẹn.
 */
class AbstractClass {
  /**
   * Phương thức template định nghĩa bộ khung của 1 thuật toán
   */
 public:
  void TemplateMethod() const {
    this->BaseOperation1();
    this->RequiredOperations1();
    this->BaseOperation2();
    this->Hook1();
    this->RequiredOperation2();
    this->BaseOperation3();
    this->Hook2();
  }
  /**
   * Các hoạt động trong thuật toán đã được implement rồi
   */
 protected:
  void BaseOperation1() const {
    std::cout << "AbstractClass says: I am doing the bulk of the work\n";
  }
  void BaseOperation2() const {
    std::cout << "AbstractClass says: But I let subclasses override some operations\n";
  }
  void BaseOperation3() const {
    std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
  }
  /**
   * Các hoạt động trong thuật toán phải được implement trong các subclass
   */
  virtual void RequiredOperations1() const = 0;
  virtual void RequiredOperation2() const = 0;
  /**
   * Các hàm dưới đây, subclass có thể override, nhưng ko bắt buộc, vì chúng đã có được
   * implement sẵn rồi, mặc dù là empty. Chúng cung cấp các điểm mở rộng bổ sung vào một số
   * nơi quan trọng của thuật toán.
   */
  virtual void Hook1() const {}
  virtual void Hook2() const {}
};
/**
 * Các class cụ thể phải implement tất cả các phương thức trừu tượng của base class.
 * Chúng có thể override 1 số phương thức với implement mặc định(như hook).
 */
class ConcreteClass1 : public AbstractClass {
 protected:
  void RequiredOperations1() const override {
    std::cout << "ConcreteClass1 says: Implemented Operation1\n";
  }
  void RequiredOperation2() const override {
    std::cout << "ConcreteClass1 says: Implemented Operation2\n";
  }
};
/**
 * Thông thường, các Concrete class override chỉ 1 phần của các phương thức của base class
 */
class ConcreteClass2 : public AbstractClass {
 protected:
  void RequiredOperations1() const override {
    std::cout << "ConcreteClass2 says: Implemented Operation1\n";
  }
  void RequiredOperation2() const override {
    std::cout << "ConcreteClass2 says: Implemented Operation2\n";
  }
  void Hook1() const override {
    std::cout << "ConcreteClass2 says: Overridden Hook1\n";
  }
};
/**
 * Client code gọi đến phương thức template để thực thi thuật toán. Client
 * code không cần phải biết class cụ thể của object nó làm việc với, miễn là nó làm việc
 * với các object thông qua interface của base class của chúng
 */
void ClientCode(AbstractClass *class_) {
  // ...
  class_->TemplateMethod();
  // ...
}

int main() {
  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass1 *concreteClass1 = new ConcreteClass1;
  ClientCode(concreteClass1);
  std::cout << "\n";
  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass2 *concreteClass2 = new ConcreteClass2;
  ClientCode(concreteClass2);
  delete concreteClass1;
  delete concreteClass2;
  return 0;
}