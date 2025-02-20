#include <iostream>
#include <algorithm>
using namespace std;

// Brute force (duyet toan bo)
void BruteForce(int a[], int n)
{
    int maxSum = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;

            for (int k = i; k <= j; k++)
                sum += a[k];

            if (sum > maxSum)
                maxSum = sum;
        }
    }
    cout << maxSum << endl;
}

// Brute force (duyet toan bo co cai tien)
void BruteForceUpdate(int a[], int n)
{
    int maxSum = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += a[j];

            if (sum > maxSum)
                maxSum = sum;
        }
    }
    cout << maxSum << endl;
}

// Recursive algorithm (thuat toan de quy)
// Hàm tìm tổng lớn nhất của đoạn con giao nhau giữa hai nửa của mảng
int MaxCrossingSum(int a[], int left, int mid, int right)
{
    int leftSum = INT16_MIN;
    int sum = 0;

    // Tính tổng từ mid về phía trái
    for (int i = mid; i >= left; i--)
    {
        sum += a[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    int rightSum = INT16_MIN;
    sum = 0;

    // Tính tổng từ mid + 1 về phía phải
    for (int i = mid + 1; i <= right; i++)
    {
        sum += a[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Tổng đoạn con lớn nhất giao giữa hai nửa
    return leftSum + rightSum;
}

// Hàm đệ quy tìm tổng đoạn con lớn nhất
int MaxSubArraySum(int a[], int left, int right)
{
    // Trường hợp cơ sở: Mảng chỉ có 1 phần tử
    if (left == right)
        return a[left];

    // Chia mảng thành hai nửa
    int mid = (left + right) / 2;

    // Tổng lớn nhất là giá trị lớn nhất trong ba trường hợp:
    // 1. Nằm hoàn toàn ở nửa trái
    // 2. Nằm hoàn toàn ở nửa phải
    // 3. Giao giữa hai nửa
    return max({MaxSubArraySum(a, left, mid),
                MaxSubArraySum(a, mid + 1, right),
                MaxCrossingSum(a, left, mid, right)});
}

// Dynamic programming (quy hoach dong) - Kadane
int DynamicProgramming(int a[], int n)
{
    int ei = a[0];
    int si = a[0];
    for (int i = 1; i < n; i++)
    {
        ei = max(a[i], a[i] + ei);
        si = max(si, ei);
    }
    return si;
}

int main()
{
    int n = 6;
    int a[n] = {-2, 11, -4, 13, -5, 2};
    BruteForce(a, n);                            // O(n^3)
    BruteForceUpdate(a, n);                      // O(n^2)
    cout << MaxSubArraySum(a, 0, n - 1) << endl; // O(nlog(n))
    cout << DynamicProgramming(a, n) << endl;    // O(n)
    return 0;
}
