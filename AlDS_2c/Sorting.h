#pragma once
#include <functional>


struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

/*
    summary
    —ортировка вставками, алгоритмическа€ сложность ........
    /summary
*/
template <class T, class TComparator = std::less<T>>
stats InsertSort(std::vector<T>& arr)
{
    stats tmp;
    int min = 0;

    for (int i = 1; i < arr.size(); i++) {
        for (int j = i; j > 0 && TComparator()(arr[j], arr[j - 1]); j--) {
            std::swap(arr[j - 1], arr[j]);
            tmp.copy_count++;
        }
        tmp.comparison_count++;
    }
    return tmp;
}

/*
    summary
    Ѕыстра€ сортировка, алгоритмическа€ сложность ........
    middleElem - ћќ∆≈“ ћ≈Ќя“№—я в процессе сортировки, на этом могут валить (:
    /summary
*/
template <class T, class TComparator = std::less <T>>
stats QuickSort(std::vector<T>& arr, int left, int right)
{
    stats tmp;
    int first = left;
    int last = right;
    T middleElem = arr[(first + last) / 2];

    do {
        while (TComparator()(arr[first], middleElem))
            first++;
        while (TComparator()(middleElem, arr[last]))
            last--;

        if (first <= last) {
            if (TComparator()(arr[last], arr[first]))
                std::swap(arr[first], arr[last]);
            first++;
            last--;
        }

    } while (first <= last);

    if (first < right)
        QuickSort(arr, first, right);
    if (left < last)
        QuickSort(arr, left, last);

    return tmp;
};


/*
    summary
    —ортировка расческой, алгоритмическа€ сложность ........
    /summary
*/
template <class T, class TComparator = std::less <T>>
stats CombSort(std::vector<T>& arr) {  //расческа
    int lng = arr.size();
    stats tmp;

    float fakt = 1.2473309;  //or float fakt = 1.3;
    int step = lng - 1;

    while (step >= 1) {
        for (int i = 0; i + step < lng; ++i) {
            if (TComparator()(arr[i + step], arr[i])) {
                std::swap(arr[i], arr[i + step]);
                tmp.copy_count++;
            }
            tmp.comparison_count++;
        }
        step /= fakt;
    }

    return tmp;
}

stats Shell_Sort(std::vector<int>& data)
{
    stats stat;
    for (size_t d = data.size() / 2; d > 0; d /= 2)
    {
        for (size_t i = d; i < data.size(); ++i)
        {
            stat.comparison_count++;
            for (int j = i - d; j >= 0 && data[j] > data[j + d]; j -= d)
            {
                int temp = data[j];
                data[j] = data[j + d];
                data[j + d] = temp;
                stat.copy_count++;
            }
        }
    }
    return stat;
}