#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include "sqllite_op.h"


void create_db_structure(SQLiteOp& sqlite_op) {
     /* Create SQL statement */
    std::string create_table_sql = "CREATE TABLE CONTACT("  \
         "id INT PRIMARY KEY     NOT NULL," \
         "first_name           TEXT    NOT NULL," \
         "last_name         TEXT    NOT NULL," \
         "email           TEXT    NOT NULL," \
         "phone           TEXT    NOT NULL," \
         "photo           TEXT    NOT NULL);";
    sqlite_op.ExecUpdate(create_table_sql);
    
    /* Create SQL statement */
    std::string insert_data_sql = "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (1, 'Fredric', 'Zhu', 'Fredric2010@outlook.com', '17366885637', 'https://img2.baidu.com/it/u=1574304958,174721775&fm=253&fmt=auto&app=138&f=JPEG?w=500&h=665'); " \
        
         "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (2, 'BoFeng', 'Tan', 'bofeng111@gmail.com', '16311112222', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2Fe167bf5b-dffc-413a-837b-ce107dc9e24d%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520553&t=0505a58fa0554700d57a8767bbc968d6'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (3, 'Lily', 'Hu', 'lilyhu123@qq.com', '16513122328', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F5737cad3-5f86-46c2-84af-67be0b3b7ca7%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520553&t=59bbd0e5ad58abb7e202e4342525a247'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (4, 'Fei', 'Zhang', 'feizhang222@163.com', '15713122326', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F8f544e0c-b753-4b51-ba8a-f08e727d0f56%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520553&t=bde67166ed212413ac87d139bd422cd5'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (5, 'Li', 'Liu', 'LiLiu333@outlook.com', '15813122328', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F3d27156b-5157-4ca1-92a3-1d471aa449f4%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520553&t=55ca224fb02d33256c16d099fa6f4bd5'); " \
        
    
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (6, 'Fei', 'Yue', 'FeiYue222@outlook.com', '15713142329', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2Fc8dbb82e-2d57-406d-89ab-4f0dbc7b01d6%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520556&t=48199667ec06c05ad0b4cc2cb569e2df'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (7, 'Jie', 'Wu', 'JieWu333@163.com', '15913152327', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2Fbc45b1ae-3876-40c9-ac79-f4f97577e779%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520556&t=78ce12b4808d5c9583a3d69b621047bf'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (8, 'JianZhong', 'Han', 'jianzhonghan@gmail.com', '15623253328', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2Fe6016b13-4d73-4d56-bd50-8174c5a2b921%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702520556&t=5957eab53850d7a6bc60e388c4326293'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (9, 'Ming', 'Li', 'mingli111@163.com', '15323263428', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F71129792-05f5-4da1-8cce-cfe96f6145f0%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702521087&t=672f6dc320f8dd0ff1e8c52c22497fa4'); " \
        
        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (10, 'San', 'Zhang', 'sanzhang222@gmail.com', '15923273429', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F3f0cd4ca-9101-41aa-a8f3-5d27b880625d%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702521087&t=84688271c47e4a8af966422680b5e9b6'); " \


        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (11, 'Wu', 'Wang', 'wuwang555@163.com', '15723293428', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F2d4476dc-f191-4a42-bfdc-7cc37d24f4bc%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702521087&t=05d5b48b730ae4013dbef7807104e4cf'); " \

        "INSERT INTO CONTACT (id,first_name,last_name,email,phone,photo) "  \
         "VALUES (12, 'Liu', 'Zhao', 'liuzhao@gmail.com', '15223293626', 'https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F983f97bf-a2dc-4696-b74c-2b14ca355c57%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1702521470&t=ccacc11910461a941ecf20a18f97922c'); ";
        
    sqlite_op.ExecUpdate(insert_data_sql);
}

int main(int argc, char* argv[]) {
    std::string db_name {"../test.db"};
    bool should_create_db {false};
    if(!boost::filesystem::exists(db_name)) {
        should_create_db = true;
    }

    SQLiteOp sqlite_op {db_name};
    sqlite_op.Open();
    
    if(should_create_db) {
        std::cout << "db not exists\n";
        create_db_structure(sqlite_op);
    }
    sqlite_op.Close();
    return EXIT_SUCCESS;
}