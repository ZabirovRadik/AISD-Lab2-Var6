#include <gtest/gtest.h>

#include <LinkedList\LinkedList.h>


TEST(DoubleConstructers, MethodTests) {
    double d_min = -100, d_max = 100;
    LinkedList<double> List3(10, d_min, d_max);
    LinkedList<double> List4(List3);
    cout << List3;
    for (size_t i = 0; i < List3.get_size(); ++i) {
        cout << List3[i] << ";  ";
        EXPECT_DOUBLE_EQ(List3[i], List4[i]);
    }
}

TEST(FloatConstructers, MethodTests) {
    float d_min = -100, d_max = 100;
    LinkedList<float> List3(10, d_min, d_max);
    LinkedList<float> List4(List3);
    for (size_t i = 0; i < List3.get_size(); ++i) {
        EXPECT_FLOAT_EQ(List3[i], List4[i]);
    }
}

TEST(ComplexDoubleConstructers, MethodTests) {
    double d_min = -100, d_max = 100;
    complex<double> z_min(d_min, d_min);
    complex<double> z_max(d_max, d_max);
    LinkedList<complex<double>> List3(10, z_min, z_max);
    LinkedList<complex<double>> List4(List3);
    cout << List3;
    for (size_t i = 0; i < List3.get_size(); ++i) {
        EXPECT_TRUE(List3[i] == List4[i]);
    }
}

TEST(ComplexFloatConstructers, MethodTests) {
    float d_min = -100, d_max = 100;
    complex<float> z_min(d_min, d_min);
    complex<float> z_max(d_max, d_max);
    LinkedList<complex<float>> List3(10, z_min, z_max);
    LinkedList<complex<float>> List4(List3);
    cout << List3;
    for (size_t i = 0; i < List3.get_size(); ++i) {
        EXPECT_TRUE(List3[i] == List4[i]);
    }
}

TEST(InsertAndDeleteDouble, MethodTests) {
    double first = 10, second = 20.10, third = 30.20, last = 40.30;
    double array[4] = { first, second, third, last };
    LinkedList<double> List;
    List.push_head(second);
    List.push_head(first);
    List.push_tail(third);
    List.push_tail(last);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(array[i], List[i]);
    }
    double array_after_delete[2] = { second, third };
    List.pop_head();
    List.pop_tail();
    EXPECT_EQ(List.get_size(), 2);
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_DOUBLE_EQ(array_after_delete[i], List[i]);
    }
}

TEST(DeleteWithCertainValue, MethodTests) {
    double to_delllllll = 10, second = 20.10, third = 30.20, last = 40.30;
    double array[4] = { second, second, third, last };
    LinkedList<double> List;
    List.push_tail(to_delllllll);
    List.push_tail(second);
    List.push_tail(to_delllllll);
    List.push_tail(second);
    List.push_tail(third);
    List.push_tail(to_delllllll);
    List.push_tail(last);
    List.push_tail(to_delllllll);
    cout << List;
    List.delete_nodes(to_delllllll);
    cout << List;

    for (size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(array[i], List[i]);
    }
}

TEST(Example1, TaskTest) {
    double first = 10, second = 20.10, third = 30.20, last = 40.30, null = 0;
    LinkedList<double> List;
    List.push_head(second);
    List.push_head(null);
    List.push_head(first);
    List.push_tail(third);
    List.push_tail(last);
    cout << List;
    EXPECT_DOUBLE_EQ(representation_polynomial<double>(List, 2),976.8);
}