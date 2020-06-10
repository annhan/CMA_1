//Toán tử ## được sử dụng để nối chuỗi hai token
//Toán tử # thông báo rằng đoạn văn bản thay thế sẽ được chuyển đổi sang một chuỗi bao quanh bởi dấu ngoặc kép.
#define COMPAREAB(a,b)	(((a)==(b)) ? true : false)
#define FOR(i,a,b)		for (int i = a; i < b; i++)
#define PENDING(NOW,SOON) ((int32_t)(NOW-(SOON))<0)
#ifdef __cplusplus
  template <class V, class N> static inline constexpr void NOLESS(V& v, const N n) {
    if (n > v) v = n;
  }
  template <class V, class N> static inline constexpr void NOMORE(V& v, const N n) {
    if (n < v) v = n;
  }
  template <class V, class N1, class N2> static inline constexpr void LIMIT(V& v, const N1 n1, const N2 n2) {
    if (n1 > v) v = n1;
    else if (n2 < v) v = n2;
  }
#else

  #define NOLESS(v, n) \
    do{ \
      __typeof__(n) _n = (n); \
      if (_n > v) v = _n; \
    }while(0)
		
  #define NOMORE(v, n) \
    do{ \
      __typeof__(n) _n = (n); \
      if (_n < v) v = _n; \
    }while(0)	

  #define LIMIT(v, n1, n2) \
    do{ \
      __typeof__(n1) _n1 = (n1); \
      __typeof__(n2) _n2 = (n2); \
      if (_n1 > v) v = _n1; \
      else if (_n2 < v) v = _n2; \
    }while(0)

#endif