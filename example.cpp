#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include "bson/bsonobj.h"
#include "bson/bsonobjbuilder.h"
#include "bson/json.h"

using namespace std;
using namespace QBson;

void bson_encode_test() {
  BsonObjBuilder bdr;
  stringstream ss(R"({x:3.14})");
  auto obj = QBson::fromjson(ss, bdr);
  double val = 3.14;
  for (int8_t* ptr = reinterpret_cast<int8_t*>(&val);
       ptr != reinterpret_cast<void*>(&val) + sizeof(val); ++ptr) {
    cout << static_cast<int>(*ptr) << " ";
  }
  cout << endl;
  auto data = obj.objdata();
  for (int i = 0; i < obj.objsize(); ++i) {
    cout << static_cast<int>(data[i]) << " ";
  }
  cout << endl;
}

void test() {
  BsonObjBuilder bdr;
  bdr.append("x", 3.14);
  bdr.append("y", 3);
  BsonObjBuilder t;
  t.append("x", 2);
  t.append("yy", bdr.obj());
  auto obj = t.obj();
  const char* bson = obj.objdata();
  string json = R"({"x": 2, "yy": {"x": 3.14, "y": 3}})";
  auto tm = chrono::system_clock::now();
  for (uint64_t res = 0;; ++res) {
    if (chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now() - tm)
            .count() > 1000) {
      cout << "bson: " << res << endl;
      break;
    }
    BsonObj ob(bson);
    ob["x"].Int();
    ob.getFieldDotted("yy.x").Double();
    ob.getFieldDotted("yy.y").Int();
  }
}

int main() {
  try {
    bson_encode_test();
  } catch (std::exception& e) {
    cerr << "exception ";
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }
  return 0;
}
