#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class SinhVien {
public:
    string ma_so;
    string ho_ten;
    string he;
    float hoc_phi;

    SinhVien(string id, string ten, string h, float phi) : ma_so(id), ho_ten(ten), he(h), hoc_phi(phi) {}
};

vector<SinhVien> sinh_vien_chinh_quy;
vector<SinhVien> sinh_vien_chat_luong_cao;

void doc_csv(const string& ten_tep_tin, vector<SinhVien>& danh_sach) {
    ifstream file(ten_tep_tin);
    if (!file.is_open()) {
        cout << "Khong the mo tep " << ten_tep_tin << endl;
        return;
    }

    string line;
    // Bỏ qua dòng tiêu đề
    getline(file, line);

    string id, ten, he;
    float hoc_phi;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '\t'); // Đọc mã số
        getline(ss, ten, '\t'); // Đọc họ và tên
        getline(ss, he, '\t'); // Đọc hệ
        // Bỏ qua các cột không cần thiết
        for (int i = 0; i < 5; ++i) {
            string temp;
            getline(ss, temp, '\t');
        }
        string hoc_phi_str;
        getline(ss, hoc_phi_str, '\t'); // Đọc học phí
        hoc_phi_str.erase(remove(hoc_phi_str.begin(), hoc_phi_str.end(), '.'), hoc_phi_str.end()); // Xóa dấu chấm
        hoc_phi = stof(hoc_phi_str); // Chuyển đổi thành kiểu float
        danh_sach.push_back(SinhVien(id, ten, he, hoc_phi));
    }

    file.close();
}

void ghi_csv(const string& ten_tep_tin, const vector<SinhVien>& danh_sach) {
    ofstream file(ten_tep_tin);
    if (!file.is_open()) {
        cout << "Khong the tao tep " << ten_tep_tin << endl;
        return;
    }

    for (const auto& sv : danh_sach) {
        file << sv.ma_so << "," << sv.ho_ten << "," << sv.he << "," << sv.hoc_phi << endl;
    }

    file.close();
}

void in_sinh_vien(const vector<SinhVien>& danh_sach) {
    for (const auto& sv : danh_sach) {
        cout << "Ma so: " << sv.ma_so << ", Ho ten: " << sv.ho_ten << ", He: " << sv.he << ", Hoc phi: " << sv.hoc_phi << endl;
    }
}

bool so_sanh_theo_hoc_phi(const SinhVien& a, const SinhVien& b) {
    return a.hoc_phi < b.hoc_phi;
}

void sap_xep_theo_hoc_phi(vector<SinhVien>& danh_sach) {
    sort(danh_sach.begin(), danh_sach.end(), so_sanh_theo_hoc_phi);
}

float tinh_hoc_phi_trung_binh(const vector<SinhVien>& danh_sach) {
    float tong_phi = 0;
    for (const auto& sv : danh_sach) {
        tong_phi += sv.hoc_phi;
    }
    return tong_phi / danh_sach.size();
}

void liet_ke_sinh_vien_cao_hon_trung_binh(const vector<SinhVien>& danh_sach, float hoc_phi_trung_binh) {
    cout << "Nhung sinh vien phai dong hoc phi cao hon muc trung binh cua ca khoa:" << endl;
    for (const auto& sv : danh_sach) {
        if (sv.hoc_phi > hoc_phi_trung_binh) {
            cout << "Ma so: " << sv.ma_so << ", Ho ten: " << sv.ho_ten << ", He: " << sv.he << ", Hoc phi: " << sv.hoc_phi << endl;
        }
    }
}

void liet_ke_5_sinh_vien_cao_nhat(const vector<SinhVien>& danh_sach) {
    cout << "5 sinh vien dong hoc phi cao nhat:" << endl;
    for (int i = 0; i < min(5, (int)danh_sach.size()); ++i) {
        cout << "Ma so: " << danh_sach[i].ma_so << ", Ho ten: " << danh_sach[i].ho_ten << ", He: " << danh_sach[i].he << ", Hoc phi: " << danh_sach[i].hoc_phi << endl;
    }
}

float tinh_hoc_phi_sinh_vien_chinh_quy(const SinhVien& sv) {
    int tong_so_tin_chi = (sv.hoc_phi / 200000) / 2;
    return tong_so_tin_chi * 200000;
}

float tinh_hoc_phi_sinh_vien_chat_luong_cao(const SinhVien& sv) {
    float hoc_phi = 20000000; // Hoc phi hoc ky 1
    for (int i = 2; i <= sv.hoc_phi; ++i) {
        hoc_phi *= 1.1; // Tang 10% moi hoc ky
    }
    return hoc_phi;
}

void tinh_va_in_hoc_phi_trung_binh() {
    float tong_phi = 0;
    int tong_sinh_vien = 0;
    for (const auto& sv : sinh_vien_chinh_quy) {
        tong_phi += tinh_hoc_phi_sinh_vien_chinh_quy(sv);
        tong_sinh_vien++;
    }
    for (const auto& sv : sinh_vien_chat_luong_cao) {
        tong_phi += tinh_hoc_phi_sinh_vien_chat_luong_cao(sv);
        tong_sinh_vien++;
    }
    float hoc_phi_trung_binh = tong_phi / tong_sinh_vien;
    cout << "Hoc phi trung binh ma sinh vien ca khoa (2 he) phai dong: " << hoc_phi_trung_binh << endl;
}

int main() {
    int lua_chon;
    do {
        cout << "===== MENU =====" << endl;
        cout << "1. Doc file CSV tu 2 danh sach" << endl;
        cout << "2. In danh sach sinh vien 2 he ra man hinh" << endl;
        cout << "3. Sap xep danh sach theo muc hoc phi tang dan o moi he" << endl;
        cout << "4. Tinh hoc phi trung binh ma sinh vien ca khoa (2 he) phai dong" << endl;
        cout << "5. Liet ke nhung sinh vien phai dong hoc phi cao hon muc trung binh cua ca khoa (2 he)" << endl;
        cout << "6. Liet ke 5 sinh vien dong hoc phi cao nhat" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        cin >> lua_chon;

        switch (lua_chon) {
            case 1:
                doc_csv("SV_CQ.csv", sinh_vien_chinh_quy);
                doc_csv("SV_CLC.csv", sinh_vien_chat_luong_cao);
                cout << "Da doc du lieu tu file CSV" << endl;
                break;
            case 2:
                cout << "Danh sach sinh vien he chinh quy:" << endl;
                in_sinh_vien(sinh_vien_chinh_quy);
                cout << endl << "Danh sach sinh vien he chat luong cao:" << endl;
                in_sinh_vien(sinh_vien_chat_luong_cao);
                break;
            case 3:
                sap_xep_theo_hoc_phi(sinh_vien_chinh_quy);
                sap_xep_theo_hoc_phi(sinh_vien_chat_luong_cao);
                cout << "Da sap xep danh sach theo muc hoc phi tang dan o moi he" << endl;
                break;
            case 4:
                tinh_va_in_hoc_phi_trung_binh();
                break;
            case 5:
                {
                    float hoc_phi_trung_binh = tinh_hoc_phi_trung_binh(sinh_vien_chinh_quy) + tinh_hoc_phi_trung_binh(sinh_vien_chat_luong_cao);
                    hoc_phi_trung_binh /= sinh_vien_chinh_quy.size() + sinh_vien_chat_luong_cao.size();
                    liet_ke_sinh_vien_cao_hon_trung_binh(sinh_vien_chinh_quy, hoc_phi_trung_binh);
                    liet_ke_sinh_vien_cao_hon_trung_binh(sinh_vien_chat_luong_cao, hoc_phi_trung_binh);
                }
                break;
            case 6:
                {
                    vector<SinhVien> tat_ca_sinh_vien(sinh_vien_chinh_quy);
                    tat_ca_sinh_vien.insert(tat_ca_sinh_vien.end(), sinh_vien_chat_luong_cao.begin(), sinh_vien_chat_luong_cao.end());
                    sap_xep_theo_hoc_phi(tat_ca_sinh_vien);
                    liet_ke_5_sinh_vien_cao_nhat(tat_ca_sinh_vien);
                }
                break;
            case 0:
                cout << "Ket thuc chuong trinh" << endl;
                break;
            default:
                cout << "Chon khong hop le. Vui long chon lai." << endl;
        }
    } while (lua_chon != 0);

    return 0;
}
