#ifndef TIEN_ICH_H
#define TIEN_ICH_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Cat khoang trang, tab va ky tu xuong dong o dau/cuoi chuoi.
string catKhoangTrang(string s);

// Kiem tra chuoi co phai so nguyen khong am hay khong.
bool laSoNguyen(string s);

// Chuyen chuoi dang so thanh double, dung chung cho so nguyen va so thuc.
double chuoiSangSo(string s);

// Nhap so nguyen trong khoang cho phep va lap lai neu nhap sai.
int nhapSo(string thongBao, int nhoNhat, int lonNhat);

// Nhap chuoi khong rong va khong chua ky tu phan tach file '|'.
string nhapChuoi(string thongBao);

// Tach mot dong text thanh cac truong bang ky tu '|'.
int tachDong(string dong, string truong[], int soTruongToiDa);

// Lay thoi gian hien tai de luu vao ket qua thi.
string layThoiGianHienTai();

// Tam dung man hinh console de nguoi dung doc ket qua.
void tamDung();

// Xao tron vector so nguyen bang thuat toan Fisher-Yates.
void xaoTronVectorSoNguyen(vector<int>& a);

// Tinh diem theo thang 10 tu so cau dung va tong so cau.
double tinhDiem(int soCauDung, int tongSoCau);

#endif
