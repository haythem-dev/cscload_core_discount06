#ifndef NMONEY_INC
#define NMONEY_INC

#ifndef MATHH_INC
    #define MATHH_INC
    #include <math.h>
#endif
#ifndef FLOATH_INC
    #define FLOATH_INC
    #include <float.h>
#endif

#ifndef MONEY_DECIMALS       /* number of decimals in */
#define MONEY_DECIMALS  2    /*   any money quantity  */
#endif                       /* don't use parentesis! */

inline double TENPOW(int n) {return pow(10.0,n);}

#define MONEY_DIG   DBL_DIG

class nMoney {
public:

    static int    decimals() { return MONEY_DECIMALS;     }
    static int    digits()   { return MONEY_DIG; }
    static double SCALE()
        { return TENPOW(MONEY_DECIMALS); }

    nMoney(){};              // do nothing constructor
    nMoney(double d) : m_money(d*SCALE()){FIX();}; // constructor from double
    nMoney(const nMoney& m)  // copy constructor
    {
      m_money = m.m_money;
    }

    nMoney& operator= (const nMoney& m)  // copy operator
    {
      m_money = m.m_money;
      return *this;
    }


    nMoney& operator= (double d)        // copy from double
    {
      m_money = d*SCALE();
      FIX();
      return *this;
    }

    operator double() const          // convert to double
    {
      return m_money / SCALE();
    }

    int  OK()   const  // check nMoney's invariant
    {
      // Returns TRUE (1) when the quantity stored
      // in *this really corresponds to a nMoney
      // quantity.

      nMoney temp;
      temp.m_money = m_money;
      temp.FIX();
      return (
               ( temp.m_money == m_money )
               &&
               ( fabs(m_money) < (TENPOW(MONEY_DIG) / SCALE()) )
             );
    }

    void FIX(int newdeci = MONEY_DECIMALS)   // get rid of unwanted decimals
    {
      // Deletes all decimals digits beyond
      // the MONEY_DECIMALS decimal place.
      // - If the value is out of range, FIX
      //   won't fix it.
      if (newdeci != MONEY_DECIMALS)
         m_money *= TENPOW(newdeci - MONEY_DECIMALS);

      m_money = (m_money > 0.0 ? floor(m_money + 0.5) : ceil(m_money - 0.5));

      if (newdeci != MONEY_DECIMALS)
         m_money /= TENPOW(newdeci - MONEY_DECIMALS);
    }


    friend nMoney  operator + (const nMoney& m, const nMoney& mm)
    {
      nMoney temp;    // don't mult*SCALE()
      temp.m_money = m.m_money + mm.m_money;
      return temp;
    }

    friend nMoney  operator + (double d, const nMoney& m)
      {return (nMoney(d)+m);}

    friend nMoney  operator + (const nMoney& m, double d)
      {return (m+nMoney(d));}

    friend nMoney  operator - (const nMoney& m, const nMoney& mm)
    {
      nMoney temp;
      temp.m_money = m.m_money - mm.m_money;
      return temp;
    }


    friend nMoney  operator - (double d, const nMoney& m)
      {return (nMoney(d)-m);}

    friend nMoney  operator - (const nMoney& m, double d)
      {return (m-nMoney(d));}

    friend nMoney  operator*  (const nMoney& m, double d)
    {
      nMoney temp;
      temp.m_money = m.m_money * d; // don't mult by SCALE()
      temp.FIX();    // this could be delayed...
      return temp;
    }

    friend nMoney  operator*  (double d, const nMoney& m)
      {return (m*d);};

    friend double operator/  (const nMoney& m, const nMoney& mm)
      {return m.m_money / mm.m_money;};

    friend nMoney  operator/  (const nMoney& m, double d)
    {
      nMoney temp;
      temp.m_money = m.m_money / d;
      temp.FIX();    // this could be delayed...
      return temp;
    }

    friend nMoney  operator%  (const nMoney& m, const nMoney& mm)
    {
      nMoney temp;
      temp.m_money = fmod(m.m_money, mm.m_money);
      temp.FIX();    // this could be delayed...
      return temp;
    }

    // nMoney  * nMoney  is NOT valid
    // double / nMoney  is INVALID

    friend int operator == (const nMoney& m, const nMoney& mm)
      {return m.m_money ==  mm.m_money;}

    friend int operator != (const nMoney& m, const nMoney& mm)
      {return m.m_money !=  mm.m_money;}

    friend int operator <  (const nMoney& m, const nMoney& mm)
      {return m.m_money <   mm.m_money;}

    friend int operator >  (const nMoney& m, const nMoney& mm)
      {return m.m_money >   mm.m_money;}

    friend int operator <= (const nMoney& m, const nMoney& mm)
      {return m.m_money <=  mm.m_money;}

    friend int operator >= (const nMoney& m, const nMoney& mm)
      {return m.m_money >=  mm.m_money;}


    nMoney& operator += (const nMoney& m)
    {
      m_money += m.m_money;
      return *this;
    }

    nMoney& operator += (double d)
    {
      m_money += d*SCALE();
      FIX();
      return *this;
    }

    nMoney& operator -= (const nMoney& m)
    {
      m_money -= m.m_money;
      return *this;
    }

    nMoney& operator -= (double d)
    {
      m_money -= d*SCALE();
      FIX();
      return *this;
    }

    nMoney& operator *= (double d)
    {
      m_money *= d;
      FIX();
      return *this;
    }

    nMoney& operator /= (double d)
    {
      m_money /= d;
      FIX();
      return *this;
    }

    nMoney  operator+ ()      // sign +
      {return *this;}

    nMoney  operator- ()      // sign -
    {
      nMoney temp;
      temp.m_money = -m_money;
      return temp;
    }

    nMoney& operator++()
    {
      m_money += SCALE();
      #if (MONEY_DECIMALS<0)
         FIX(); // avoid problems because of
      #endif     // the representation of 10^-n
      return *this;
    }

    nMoney& operator--()
    {
      m_money -= SCALE();
      #if (MONEY_DECIMALS<0)
         FIX();
      #endif
      return *this;
    }

    nMoney operator++(int)
    {
      nMoney temp;
      temp.m_money = m_money;
      m_money += SCALE();
      #if (MONEY_DECIMALS<0)
         FIX(); // avoid problems because of
      #endif     // the representation of 10^-n
      return temp;
    }

    nMoney operator--(int)
    {
      nMoney temp;
      temp.m_money = m_money;
      m_money -= SCALE();
      #if (MONEY_DECIMALS<0)
         FIX();
      #endif
      return temp;
    }

    friend int    operator! (const nMoney& m)
      {return m.m_money == 0.0;}

    friend nMoney abs(const nMoney& m)
    {
      nMoney temp;
      temp.m_money = fabs(m.m_money);
      return temp;
    }

    friend nMoney flatten(const nMoney& m,
                          double cents=0.25,
                          int rounding = 1 /* TRUE */)
    {
      // Returns a nMoney data item where the cents are
      // rounded modulo "cents". In this way cents can
      // be stripped of nMoney items when the currency
      // does not have all the coins required to pay
      // every posible quantity.
      nMoney temp;
      double c = floor(fabs(cents*nMoney::SCALE())); // cents
      double r = fmod(m.m_money, c);            // remainder
      temp.m_money = (!rounding || (2.0* r <= c) ?
                      m.m_money - r : m.m_money - r + c);
      return temp;
    }


protected:         // let users change the class behaviour
    double m_money;
};

#endif
