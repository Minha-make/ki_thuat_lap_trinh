#ifndef DU_LIEU_H
#define DU_LIEU_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SO_DAP_AN = 4;
extern const char FILE_MON_HOC[];
extern const char FILE_CAU_HOI[];
extern const char FILE_THI_SINH[];
extern const char FILE_KET_QUA[];

struct MonHoc {
    int maMonHoc;
    string tenMonHoc;
};

struct CauHoi {
    int maCauHoi;
    int maMonHoc;
    int mucDo; // 1: De, 2 tro len: Kho
    string noiDung;
    string dapAn[SO_DAP_AN];
    int dapAnDung; // 0=A, 1=B, 2=C, 3=D
};

struct ThiSinh {
    int maThiSinh;
    string hoTen;
};

struct CauHoiThi {
    int maCauHoi;
    vector<int> thuTuDapAn;
    int dapAnDaChon; // chi so dap an goc, -1 neu bo qua
};

struct KetQuaThi {
    int maKetQua;
    int maThiSinh;
    int maMonHoc;
    int tongSoCau;
    int soCauDung;
    string thoiGianThi;
    int thoiGianLamBaiGiay;
};

extern vector<MonHoc> dsMonHoc;
extern vector<CauHoi> dsCauHoi;
extern vector<ThiSinh> dsThiSinh;
extern vector<KetQuaThi> dsKetQua;

string catKhoangTrang(string s);
bool laSoNguyen(string s);
double chuoiSangSo(string s);
int nhapSo(string thongBao, int nhoNhat, int lonNhat);
string nhapChuoi(string thongBao);
int tachDong(string dong, string truong[], int soTruongToiDa);
string layThoiGianHienTai();
void tamDung();
void xaoTronVectorSoNguyen(vector<int>& a);
double tinhDiem(int soCauDung, int tongSoCau);
void docDuLieu();
void ghiDuLieu();
int timMonHoc(int maMonHoc);
int timThiSinh(int maThiSinh);
int timCauHoi(int maCauHoi);

#endif
