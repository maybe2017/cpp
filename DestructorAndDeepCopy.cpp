
// 代码区: 函数二进制数据，共享只读(就算启动多个相同进程，内存也只有一份数据，静态链接库与动态链接库??)
// 全局区: 静态变量static、全局变量(不在函数体内)、const全局常量(强调只读)、字符串常量

// 运行时产生的区域
// 栈区: 函数体形参、局部变量、返回值、const修饰的局部常量，编译器自行分配及回收。 -->> 不要返回局部变量的地址(释放后地址非法)
// 堆区: 程序员自行开辟，也需要自行销毁，否则只有等待进程结束，才会被操作系统回收。


// 复制
// 函数的传参: 值传递、指针传递、引用传递
// 函数的返回值: 返回值(复制整个对象 -> 会产生构造函数与析构函数的调用)、
// 返回指针(复制地址8字节、但是指针是右值)、返回引用(复制别名、是左值) -->> 不要返回函数执行结束后会被编译器回收的地址或引用(释放后地址非法)

// 左值: 表示可寻址, 有确切地址，并能取地址，进行访问，修改等操作的表达式
// 右值: 表示可读不可寻址。是保存在内存中，或者寄存器中，不知道也无法获得其确切地址，在得到计算表达式结果后就销毁的临时表达式


// 初始化列表方式的构造函数
// 嵌套类 属性用初始化列表赋值 构造与析构的顺序问题
// Static类变量 为啥必须在类外初始化？？

// 空对象字节数 内存对齐？？成员函数与静态函数的存放位置 this指针(空指针可以调用成员函数，函数内注意this判空？？)
// 链式调用函数的写法 要返回引用 而不是值（注意拷贝函数的调用场景）
// 每个成员函数中默认会有个this指针，本质-指针常量，const常函数（相当于双const修饰）
// const常函数的写法，本质是(确保不能修改没有加mutable的属性)；常对象，常对象只能调用常函数(确保不能修改没有加mutable的属性)

// 全局函数做友元、类做友元、类中的成员函数 可实现访问私有成员

// 运算符重载 << 递增 注意前置与后置返回值 是引用还是值

// =赋值运算符重载 注意浅拷贝引发的内存重复释放问题(=重载与拷贝构造重载实现中解决)
// 函数调用符()重载 仿函数 注意匿名对象调用仿函数的方式


// 继承(多重)写法 class 子类: 继承方式(public、protect、private) 父类, 继承方式(public、protect、private) 父类
// 首先，无论如何，子类不能访问父类的私有成员（私有变量可以通过父类protect、public的方法进行访问，与Java一样的道理）
// protect继承: 父类的public属性在子类中被升级为protect权限
// private继承：父类的public及protect属性在子类中被升级为private权限

// 虚继承写法 class 子类: virtual 继承方式(public、protect、private) 父类；解决菱形继承子类存在多份父类相同变量的数据问题(vbptr)
// 动态多态: 虚函数可以实现让形式参数的地址晚绑定(虚函数使基类函数的地址不确定) 从而实现运行时多态(子类重写了父类的虚函数: 注意，重写了那么)
// 子类重写了父类的虚函数: 注意，重写了那么子类该函数也是虚函数! 所以子类有自己的虚函数表，该方法指针vfptr(占8字节)，指向子类自身的虚函数地址，所以运行时调用的是自身的方法。
// vbptr 虚基类指针 指向 虚基类表；vfptr 虚函数指针 指向 虚函数表
// 创建对象时，创建虚函数表指针; 虚函数表(类层级)是编译器在编译期间确定。

// 只要含有一个纯虚函数(没有默认实现)就是抽象类，该类不能实例化；类中可以有其他虚函数(带有默认实现)或其他方法、变量等；与Java抽象类很相似
// Java带final的方法就是C++中普通的方法；不带final的就是C++中的虚函数
// 抽象到极致就是接口；C++里面没有同Java中专门定义接口的关键字interface；而是就是用抽象类来表示，只是这个抽象类中可全是纯虚函数就行，当然也可以有静态变量等

// 父类虚析构函数作用: 解决当父类指针指向子类对象时，对父类指针的delete不会调用子类的析构函数，只会调用父类的；设置父类虚析构函数后，就会先调用子类的，后父类。
// 父类的纯虚析构: 坑，虽然也能解决上面的问题，但是纯虚析构不仅需要声明，还需要在类外定义(目的是释放父类自身在堆区开辟的内存)。
// 纯虚析构的目的: 强制子类重写析构函数。virtual ~Person()=0; 或者virtual ~Person()=default;