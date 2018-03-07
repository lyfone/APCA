#include <iostream>
#include<ctime>
#include "APCA.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    srand((unsigned) time(NULL));
    APCA apca(20);
    for(int i=0;i<20;i++){
        int tmp = rand() % 100;
        bool flag = apca.push(tmp);
        if(!flag){
            int k = 0;
            vector<float> result = apca.get_points();
            cout << "width : " << apca.get_width() << endl;
            for(auto it = result.begin();it != result.end();it++)
                cout << "data " << ++k << " : " << *it << endl;
            cout << "sum : " << apca.get_sum() << endl;
            cout << "avg : " << apca.get_avg() << endl;
            apca.reset();
            apca.push(tmp);
        }
    }
    if(apca.get_points().size()){
        int k = 0;
        vector<float> result = apca.get_points();
        cout << "width : " << apca.get_width() << endl;
        for(auto it = result.begin();it != result.end();it++)
            cout << "data " << ++k << " : " << *it << endl;
        cout << "sum : " << apca.get_sum() << endl;
        cout << "avg : " << apca.get_avg() << endl;
        apca.reset();
    }

    return 0;
}