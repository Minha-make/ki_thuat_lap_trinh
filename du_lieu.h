#ifndef DU_LIEU_H
#define DU_LIEU_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "tien_ich.h"

using namespace std;

// Hang so dung chung cho toan chuong trinh.
const int SO_DAP_AN = 4;

// Ten cac file text dung de luu du lieu lau dai.
extern const char FILE_MON_HOC[];
extern const char FILE_CAU_HOI[];
extern const char FILE_THI_SINH[];
extern const char FILE_KET_QUA[];

// Luu thong tin mot mon hoc/hoc phan.
struct MonHoc {
    int maMonHoc;
    string tenMonHoc;
};

// Luu thong tin mot cau hoi trong ngan hang cau hoi.
struct CauHoi {
    int maCauHoi;
    int maMonHoc;
    int mucDo; // 1: De, 2 tro len: Kho
    string noiDung;
    string dapAn[SO_DAP_AN];
    int dapAnDung; // 0=A, 1=B, 2=C, 3=D
};

// Luu thong tin thi sinh.
struct ThiSinh {
    int maThiSinh;
    string hoTen;
};

// Luu mot cau hoi da duoc dua vao de thi.
struct CauHoiThi {
    int maCauHoi;
    vector<int> thuTuDapAn;
    int dapAnDaChon; // chi so dap an goc, -1 neu bo qua
};

// Luu ket qua cua mot lan thi.
struct KetQuaThi {
    int maKetQua;
    int maThiSinh;
    int maMonHoc;
    int tongSoCau;
    int soCauDung;
    string thoiGianThi;
    int thoiGianLamBaiGiay;
};

// Cac danh sach du lieu dung chung, duoc dinh nghia that trong du_lieu.cpp.
extern vector<MonHoc> dsMonHoc;
extern vector<CauHoi> dsCauHoi;
extern vector<ThiSinh> dsThiSinh;
extern vector<KetQuaThi> dsKetQua;

// Nhom ham doc/ghi file: nap du lieu vao vector va luu vector ra file text.
void docDuLieu();
void ghiDuLieu();

// Nhom ham tim kiem dung chung cho cac module khac.
int timMonHoc(int maMonHoc);
int timThiSinh(int maThiSinh);
int timCauHoi(int maCauHoi);

#endif
