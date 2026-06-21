#ifndef THI_H
#define THI_H

#include "ngan_hang_cau_hoi.h"

// Tao mot cau hoi trong de thi tu chi so cau hoi goc va xao tron dap an.
void themCauHoiVaoDeThi(int chiSoCauHoi, vector<CauHoiThi>& deThi);

// Lay ngau nhien mot so cau hoi de/kho cua mot mon de dua vao de thi.
void themCauHoiTheoLoaiVaoDe(int maMonHoc, int loaiCauHoi, int soCauCanLay, vector<CauHoiThi>& deThi);

// Sinh de thi theo cau hinh so cau de, so cau kho va xao tron thu tu cau hoi.
void sinhDeThi(int maMonHoc, int soCauDe, int soCauKho, vector<CauHoiThi>& deThi);

// Kiem tra thoi gian lam bai da het hay chua.
bool hetGio(time_t batDau, int soPhut);

// Dieu khien qua trinh lam bai, nhap dap an va tu dong thu bai khi het gio.
void lamBaiThi(vector<CauHoiThi>& deThi, int soPhut, int& thoiGianLamBaiGiay);

// Dieu phoi toan bo quy trinh: chon thi sinh, chon mon, sinh de, lam bai, cham diem.
void batDauThi();

#endif
