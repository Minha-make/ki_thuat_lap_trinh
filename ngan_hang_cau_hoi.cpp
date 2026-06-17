#include "ngan_hang_cau_hoi.h"

int sinhMaCauHoiMoi() {
    int maLonNhat = 0;
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        if (dsCauHoi[i].maCauHoi > maLonNhat) {
            maLonNhat = dsCauHoi[i].maCauHoi;
        }
    }
    return maLonNhat + 1;
}

// Hien thi danh sach mon hoc/hoc phan.
void hienThiMonHoc() {
    cout << "\nDANH SACH MON HOC\n";
    cout << left << setw(8) << "Ma" << setw(40) << "Ten mon hoc" << "\n";
    for (int i = 0; i < static_cast<int>(dsMonHoc.size()); i++) {
        cout << left << setw(8) << dsMonHoc[i].maMonHoc
             << setw(40) << dsMonHoc[i].tenMonHoc << "\n";
    }
}

// Hien thi cac cau hoi dang hoat dong cua mot mon hoc.
void hienThiCauHoiTheoMon() {
    hienThiMonHoc();
    int maMonHoc = nhapSo("Nhap ma mon hoc can xem: ", 1, 1000000);
    int dem = 0;

    cout << "\nDANH SACH CAU HOI\n";
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        CauHoi ch = dsCauHoi[i];
        if (ch.maMonHoc == maMonHoc) {
            cout << "\nMa cau hoi: " << ch.maCauHoi << "\n";
            cout << "Muc do: " << (ch.mucDo == 1 ? "De" : "Kho") << "\n";
            cout << "Noi dung: " << ch.noiDung << "\n";
            cout << "A. " << ch.dapAn[0] << "\n";
            cout << "B. " << ch.dapAn[1] << "\n";
            cout << "C. " << ch.dapAn[2] << "\n";
            cout << "D. " << ch.dapAn[3] << "\n";
            cout << "Dap an dung: " << char('A' + ch.dapAnDung) << "\n";
            dem++;
        }
    }

    if (dem == 0) cout << "Khong co cau hoi cho mon nay.\n";
}

// Nhap va them mot cau hoi moi vao ngan hang cau hoi.
void themCauHoi() {
    CauHoi ch;
    hienThiMonHoc();

    ch.maCauHoi = sinhMaCauHoiMoi();
    ch.maMonHoc = nhapSo("Nhap ma mon hoc: ", 1, 1000000);
    if (timMonHoc(ch.maMonHoc) == -1) {
        cout << "Ma mon hoc khong ton tai.\n";
        return;
    }

    ch.mucDo = nhapSo("Nhap muc do (1=De, 2=Kho): ", 1, 2);
    ch.noiDung = nhapChuoi("Nhap noi dung cau hoi: ");
    ch.dapAn[0] = nhapChuoi("Nhap dap an A: ");
    ch.dapAn[1] = nhapChuoi("Nhap dap an B: ");
    ch.dapAn[2] = nhapChuoi("Nhap dap an C: ");
    ch.dapAn[3] = nhapChuoi("Nhap dap an D: ");
    ch.dapAnDung = nhapSo("Nhap dap an dung (0=A, 1=B, 2=C, 3=D): ", 0, 3);
    dsCauHoi.push_back(ch);
    ghiDuLieu();
    cout << "Da them cau hoi moi, ma cau hoi = " << ch.maCauHoi << ".\n";
}

// Kiem tra cau hoi co dung mon hoc va dung loai de/kho hay khong.
bool laCauHoiDungLoai(CauHoi ch, int maMonHoc, int loaiCauHoi) {
    if (ch.maMonHoc != maMonHoc) {
        return false;
    }

    if (loaiCauHoi == 1) {
        return ch.mucDo == 1;
    }

    return ch.mucDo >= 2;
}

// Dem so cau hoi dang hoat dong theo mon hoc va muc do de/kho.
int demCauHoiTheoMonVaLoai(int maMonHoc, int loaiCauHoi) {
    int dem = 0;
    for (int i = 0; i < static_cast<int>(dsCauHoi.size()); i++) {
        if (laCauHoiDungLoai(dsCauHoi[i], maMonHoc, loaiCauHoi)) {
            dem++;
        }
    }
    return dem;
}

// Dieu khien menu quan ly ngan hang cau hoi.
void menuNganHangCauHoi() {
    while (true) {
        cout << "\n===== NGAN HANG CAU HOI =====\n";
        cout << "1. Xem danh sach mon hoc\n";
        cout << "2. Xem cau hoi theo mon hoc\n";
        cout << "3. Them cau hoi\n";
        cout << "0. Quay lai\n";

        int chon = nhapSo("Chon: ", 0, 3);
        if (chon == 0) return;
        if (chon == 1) hienThiMonHoc();
        if (chon == 2) hienThiCauHoiTheoMon();
        if (chon == 3) themCauHoi();
        tamDung();
    }
}

// ==================================================
// 8. THI: SINH DE, XAO TRON, TINH GIO
// ==================================================


