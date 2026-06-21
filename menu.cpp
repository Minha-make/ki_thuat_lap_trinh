#include "menu.h"

// Hien thi menu chinh va dieu huong den ngan hang cau hoi, thi, bao cao hoac thoat.
void menuChinh() {
    while (true) {
        cout << "\n===== CHUONG TRINH THI TRAC NGHIEM =====\n";
        cout << "1. Quan ly ngan hang cau hoi\n";
        cout << "2. Cau hinh de thi va bat dau thi\n";
        cout << "3. Bao cao ket qua thi\n";
        cout << "0. Luu va thoat\n";

        int chon = nhapSo("Chon: ", 0, 3);
        if (chon == 0) {
            ghiDuLieu();
            cout << "Da luu du lieu.\n";
            return;
        }
        if (chon == 1) menuNganHangCauHoi();
        if (chon == 2) {
            batDauThi();
            tamDung();
        }
        if (chon == 3) {
            hienThiBaoCaoKetQua();
            tamDung();
        }
    }
}
