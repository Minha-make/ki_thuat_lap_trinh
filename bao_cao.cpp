#include "bao_cao.h"

// Dem so cau tra loi dung bang cach so sanh dap an da chon voi dap an dung goc.
int demCauDung(vector<CauHoiThi>& deThi) {
    int dem = 0;
    for (int i = 0; i < static_cast<int>(deThi.size()); i++) {
        int viTri = timCauHoi(deThi[i].maCauHoi);
        if (viTri != -1 && deThi[i].dapAnDaChon == dsCauHoi[viTri].dapAnDung) {
            dem++;
        }
    }
    return dem;
}

// Sinh ma ket qua moi bang cach lay ma ket qua lon nhat hien co cong 1.
int sinhMaKetQuaMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < static_cast<int>(dsKetQua.size()); i++) {
        if (dsKetQua[i].maKetQua > maLonNhat) {
            maLonNhat = dsKetQua[i].maKetQua;
        }
    }
    return maLonNhat + 1;
}

// Luu ket qua thi vao dsKetQua, ghi file va in diem; diem khong luu truc tiep trong file.
void luuKetQua(int maThiSinh, int maMonHoc, int tongSoCau, int soCauDung, int thoiGianLamBaiGiay) {
    KetQuaThi kq;
    kq.maKetQua = sinhMaKetQuaMoi();
    kq.maThiSinh = maThiSinh;
    kq.maMonHoc = maMonHoc;
    kq.tongSoCau = tongSoCau;
    kq.soCauDung = soCauDung;
    kq.thoiGianThi = layThoiGianHienTai();
    kq.thoiGianLamBaiGiay = thoiGianLamBaiGiay;

    dsKetQua.push_back(kq);
    ghiDuLieu();

    cout << "\n===== KET QUA THI =====\n";
    cout << "So cau dung: " << soCauDung << "/" << tongSoCau << "\n";
    cout << fixed << setprecision(2);
    cout << "Diem: " << tinhDiem(soCauDung, tongSoCau) << "\n";
    cout << "Thoi gian lam bai: " << thoiGianLamBaiGiay << " giay\n";
}

// Hien thi tat ca ket qua thi va thong ke diem cao nhat, thap nhat, trung binh.
void hienThiBaoCaoKetQua() {
    if (static_cast<int>(dsKetQua.size()) == 0) {
        cout << "Chua co ket qua thi.\n";
        return;
    }

    cout << "\nBAO CAO KET QUA NHIEU LAN THI\n";
    cout << left
         << setw(8) << "MaKQ"
         << setw(8) << "MaTS"
         << setw(8) << "MaMH"
         << setw(10) << "Tong"
         << setw(10) << "Dung"
         << setw(10) << "Diem"
         << setw(22) << "Thoi gian"
         << setw(8) << "Giay" << "\n";

    double diemDauTien = tinhDiem(dsKetQua[0].soCauDung, dsKetQua[0].tongSoCau);
    double tongDiem = 0;
    double caoNhat = diemDauTien;
    double thapNhat = diemDauTien;

    for (int i = 0; i < static_cast<int>(dsKetQua.size()); i++) {
        KetQuaThi kq = dsKetQua[i];
        double diem = tinhDiem(kq.soCauDung, kq.tongSoCau);
        cout << left
             << setw(8) << kq.maKetQua
             << setw(8) << kq.maThiSinh
             << setw(8) << kq.maMonHoc
             << setw(10) << kq.tongSoCau
             << setw(10) << kq.soCauDung
             << setw(10) << fixed << setprecision(2) << diem
             << setw(22) << kq.thoiGianThi
             << setw(8) << kq.thoiGianLamBaiGiay << "\n";

        tongDiem += diem;
        if (diem > caoNhat) caoNhat = diem;
        if (diem < thapNhat) thapNhat = diem;
    }

    cout << "\nSo lan thi: " << static_cast<int>(dsKetQua.size()) << "\n";
    cout << "Diem cao nhat: " << caoNhat << "\n";
    cout << "Diem thap nhat: " << thapNhat << "\n";
    cout << "Diem trung binh: " << tongDiem / static_cast<int>(dsKetQua.size()) << "\n";
}
