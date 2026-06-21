#ifndef BAO_CAO_H
#define BAO_CAO_H

#include <iomanip>

#include "du_lieu.h"

// Dem so cau tra loi dung sau khi thi sinh lam bai.
int demCauDung(vector<CauHoiThi>& deThi);

// Sinh ma ket qua moi de luu mot lan thi.
int sinhMaKetQuaMoi();

// Luu ket qua thi vao danh sach va ghi ra file results.txt.
void luuKetQua(int maThiSinh, int maMonHoc, int tongSoCau, int soCauDung, int thoiGianLamBaiGiay);

// In bao cao ket qua cua tat ca cac lan thi.
void hienThiBaoCaoKetQua();

#endif
