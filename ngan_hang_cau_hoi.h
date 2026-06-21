#ifndef NGAN_HANG_CAU_HOI_H
#define NGAN_HANG_CAU_HOI_H

#include "du_lieu.h"

// Sinh ma cau hoi moi dua tren ma lon nhat dang co trong dsCauHoi.
int sinhMaCauHoiMoi();

// In danh sach mon hoc de nguoi dung chon khi xem/them cau hoi.
void hienThiMonHoc();

// Cho nguoi dung chon mon hoc va in tat ca cau hoi thuoc mon do.
void hienThiCauHoiTheoMon();

// Nhap thong tin va them mot cau hoi moi vao ngan hang cau hoi.
void themCauHoi();

// Kiem tra mot cau hoi co dung mon va dung loai de/kho hay khong.
bool laCauHoiDungLoai(CauHoi ch, int maMonHoc, int loaiCauHoi);

// Dem so cau hoi cua mot mon theo loai de hoac kho.
int demCauHoiTheoMonVaLoai(int maMonHoc, int loaiCauHoi);

// Menu con cho nhom thao tac quan ly ngan hang cau hoi.
void menuNganHangCauHoi();

#endif
