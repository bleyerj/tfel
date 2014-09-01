/*!
 * \file   include/TFEL/Math/tmatrix.hxx  
 * \brief    
 * \author Helfer Thomas
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _TFEL_MATH_TINY_MATRIX_LIB_
#define _TFEL_MATH_TINY_MATRIX_LIB_ 1

#include <string>
#include <cstddef>
#include <ostream>

#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/TypeTraits/IsAssignableTo.hxx"

#include"TFEL/Math/fsarray.hxx"
#include"TFEL/Math/General/BasicOperations.hxx"
#include"TFEL/Math/General/EmptyRunTimeProperties.hxx"
#include"TFEL/Math/Function/Power.hxx"

#include"TFEL/Math/Matrix/MatrixConcept.hxx"
#include"TFEL/Math/Matrix/MatrixConceptOperations.hxx"
#include"TFEL/Math/Matrix/MatrixExpr.hxx"
#include"TFEL/Math/tvector.hxx"

#include"TFEL/Math/Forward/tmatrix.hxx"

namespace tfel{
  
  namespace math{

    //! Partial specialisation for tmatrixs.
    /*
     * This is a MatrixConcept requirement.
     * \see MatrixTraits.
     */
    template<unsigned short N,unsigned short M, typename T>
    struct TFEL_VISIBILITY_LOCAL MatrixTraits<tmatrix<N,M,T> >{
      //! the type holded by the tmatrix.
      typedef T NumType;
      //! the type of the index used by the tmatrix.
      typedef unsigned short IndexType;
      //! a simple typedef to the tmatrix runtime properties
      typedef EmptyRunTimeProperties RunTimeProperties;
    };
    
    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short K,typename T>
    struct tmatrix_row_view;

    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short K,typename T>
    struct tmatrix_const_row_view;

    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short K,typename T>
    struct tmatrix_column_view;

    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short K,typename T>
    struct tmatrix_const_column_view;

    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short R,unsigned short C,
	     typename T>
    struct tmatrix_submatrix_view;

    // forward declaration
    template<unsigned short N,unsigned short M,
	     unsigned short I,unsigned short J,
	     unsigned short R,unsigned short C,
	     typename T>
    struct tmatrix_const_submatrix_view;

    /*!
     * \brief a base for tmatrix or classes acting like tmatrix.
     */
    template<typename Child,
	     unsigned short N,
	     unsigned short M,
	     typename T>
    struct tmatrix_base
    {
      // Assignement operator
      /*
       * \param const MatrixExpr<tmatrix<N,T2>,Expr>&, a matrix expression.
       * \return Child& a reference to this.
       * \pre T2 must be assignable to a T.
       */
      template<typename T2,typename Expr>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator=(const MatrixExpr<tmatrix<N,M,T2>,Expr>&);
      // Assignement operator
      template<typename T2>
      TFEL_MATH_INLINE
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator=(const tmatrix<N,M,T2>&);
      // Assignement operator
      /*
       * \param const MatrixExpr<tmatrix<N,T2>,Expr>&, a matrix expression.
       * \return Child& a reference to this.
       * \pre T2 must be assignable to a T.
       */
      template<typename T2,typename Expr>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator+=(const MatrixExpr<tmatrix<N,M,T2>,Expr>&);
      // Assignement operator
      template<typename T2>
      TFEL_MATH_INLINE
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator+=(const tmatrix<N,M,T2>&);
      // Assignement operator
      /*
       * \param const MatrixExpr<tmatrix<N,T2>,Expr>&, a matrix expression.
       * \return Child& a reference to this.
       * \pre T2 must be assignable to a T.
       */
      template<typename T2,typename Expr>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator-=(const MatrixExpr<tmatrix<N,M,T2>,Expr>&);
      // Assignement operator
      template<typename T2>
      TFEL_MATH_INLINE
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	Child&
      >::type
      operator-=(const tmatrix<N,M,T2>&);
      /*!
       * operator*=
       */
      template<typename T2>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsScalar<T2>::cond&&
      tfel::meta::IsSameType<typename ResultType<T,T2,OpMult>::type,T>::cond,
	Child&
      >::type
      operator*=(const T2);
      /*!
       * operator/=
       */
      template<typename T2>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsScalar<T2>::cond&&
        tfel::meta::IsSameType<typename ResultType<T,T2,OpMult>::type,T>::cond,
	Child&
      >::type
      operator/=(const T2);
    };

    template<unsigned short N,unsigned short M,
	     typename T = double>
    struct tmatrix
      : public MatrixConcept<tmatrix<N,M,T> >,
	public tmatrix_base<tmatrix<N,M,T>,N,M,T>,
	public fsarray<N*M,T>
    {
      //! a simple typedef to the tmatrix runtime properties
      /*
       * This is a MatrixConcept requirement.
       */
      typedef EmptyRunTimeProperties RunTimeProperties;
      /*!
       * Default constructor.
       */
      TFEL_MATH_INLINE
      tmatrix();
      /*!
       * Constructor from a scalar.
       * \param const T : initial value.
       */
      explicit
      TFEL_MATH_INLINE
      tmatrix(const T);
      /*
       * Constructor from a pointer.
       * \param const T* : initial values.
       */
      explicit TFEL_MATH_INLINE
      tmatrix(const T* const);
      /*!
       * \brief index operator (const version).
       * This is a matrix concept requirement.
       * \param const unsigned short, row index.
       * \param const unsigned short, column index.
       * \return const T&, a reference to the tmatrix ith element.
       */
      TFEL_MATH_INLINE
      const T&
      operator()(const unsigned short,const unsigned short) const;
      /*!
       * \brief index operator.
       * \param const unsigned short, row index.
       * \param const unsigned short, column index.
       * \return T&, a reference to the tmatrix ith element.
       */
      TFEL_MATH_INLINE
      T&
      operator()(const unsigned short,const unsigned short);
      //! Return the RunTimeProperties of the tmatrix.
      /*
       * This is a MatrixConcept requirement.
       * \return const RunTimeProperties, the runtime properties of
       * the tmatrix
       */
      TFEL_MATH_INLINE
      RunTimeProperties
      getRunTimeProperties(void) const
      {
	return RunTimeProperties();
      }
      
      TFEL_MATH_INLINE2
      unsigned short getNbCols(void) const ;

      TFEL_MATH_INLINE2
      unsigned short getNbRows(void) const ;
      /*!
       * \return a view of a row of this matrix
       * \param[in] I : row index
       */
      template<unsigned short I>
      tmatrix_row_view<N,M,I,0,M,T>
      row_view();
      /*!
       * \return a view of a slice of row of this matrix
       * \param[in] I : row index
       * \param[in] J : starting index in the row
       * \param[in] K : size of the slice
       */
      template<unsigned short I,unsigned short J,unsigned short K>
      tmatrix_row_view<N,M,I,J,K,T>
      row_view();
      /*!
       * \return a view of a row of this matrix
       * \param[in] I : row index
       */
      template<unsigned short I>
      tmatrix_const_row_view<N,M,I,0,M,T>
      row_view() const;
      /*!
       * \return a view of a slice of row of this matrix
       * \param[in] I : row index
       * \param[in] J : starting index in the row
       * \param[in] K : size of the slice
       */
      template<unsigned short I,unsigned short J,unsigned short K>
      tmatrix_const_row_view<N,M,I,J,K,T>
      row_view() const;
      /*!
       * \return a view of a column of this matrix
       * \param[in] I : column index
       */
      template<unsigned short I>
      tmatrix_column_view<N,M,I,0,N,T>
      column_view();
      /*!
       * \return a view of a slice of column of this matrix
       * \param[in] I : column index
       * \param[in] J : starting index in the column
       * \param[in] K : size of the slice
       */
      template<unsigned short I,
	       unsigned short J,
	       unsigned short K>
      tmatrix_column_view<N,M,I,J,K,T>
      column_view();
      /*!
       * \return a view of a slice of column of this matrix
       * \param[in] I : column index
       * \param[in] J : starting index in the column
       * \param[in] K : size of the slice
       */
      template<unsigned short I,
	       unsigned short J,
	       unsigned short K>
      tmatrix_const_column_view<N,M,I,J,K,T>
      column_view() const;
      /*!
       * \return a view of a column of this matrix
       * \param[in] I : column index
       */
      template<unsigned short I>
      tmatrix_const_column_view<N,M,I,0,N,T>
      column_view() const;
      /*!
       * \return a view of a sub matrix of this matrix
       * \param[in] I : submatrix row    starting index
       * \param[in] J : submatrix column starting index
       * \param[in] R : number of rows
       * \param[in] C : number of columns
       */
      template<unsigned short I,unsigned short J,
	       unsigned short R,unsigned short C>
      tmatrix_submatrix_view<N,M,I,J,R,C,T>
      submatrix_view();
      /*!
       * \return a view of a sub matrix of this matrix
       * \param[in] I : submatrix row    starting index
       * \param[in] J : submatrix column starting index
       * \param[in] R : number of rows
       * \param[in] C : number of columns
       */
      template<unsigned short I,unsigned short J,
	       unsigned short R,unsigned short C>
      tmatrix_const_submatrix_view<N,M,I,J,R,C,T>
      submatrix_view() const;

      TFEL_MATH_INLINE2
      T max(void) const ;

      TFEL_MATH_INLINE2
      T abs_max(void) const ;

      TFEL_MATH_INLINE2
      void swap_rows(const unsigned short i,const unsigned short j);
      
      static tmatrix<N,N,T> Id(void);
      /*!
       * copy the N*Mth elements following this argument.
       * \param const InputIterator, an iterator to the first element
       * to be copied.
       */
      template<typename InputIterator>
      TFEL_MATH_INLINE2 void
      copy(const InputIterator);

      //! using tmatrix_base::operator=
      using tmatrix_base<tmatrix,N,M,T>::operator=;
      //! using tmatrix_base::operator+=
      using tmatrix_base<tmatrix,N,M,T>::operator+=;
      //! using tmatrix_base::operator-=
      using tmatrix_base<tmatrix,N,M,T>::operator-=;
      //! using tmatrix_base::operator*=
      using tmatrix_base<tmatrix,N,M,T>::operator*=;
      //! using tmatrix_base::operator/=
      using tmatrix_base<tmatrix,N,M,T>::operator/=;
    private:
      //! a simple assertion stating that the number of row is valid.
      TFEL_STATIC_ASSERT(N!=0);
      //! a simple assertion stating that the number of column is valid.
      TFEL_STATIC_ASSERT(M!=0);
    };

    // Transpose
    template<unsigned short N,unsigned short M,typename T>
    TFEL_MATH_INLINE2
    tmatrix<M,N,T> transpose(const tmatrix<N,M,T>&);

    template<typename T,
	     typename Expr>
    TFEL_MATH_INLINE
    typename ComputeUnaryResult<T,Power<3> >::Result
    det(const MatrixExpr<tmatrix<2,2,T>,Expr>&);
    
    template<typename T>
    TFEL_MATH_INLINE
    typename ComputeUnaryResult<T,Power<3> >::Result
    det(const tmatrix<2,2,T>&);

    template<typename T,
	     typename Expr>
    TFEL_MATH_INLINE
    typename ComputeUnaryResult<T,Power<3> >::Result
    det(const MatrixExpr<tmatrix<3,3,T>,Expr>&);
    
    template<typename T>
    TFEL_MATH_INLINE
    typename ComputeUnaryResult<T,Power<3> >::Result
    det(const tmatrix<3,3,T>&);

    // Serialisation operator
    template<unsigned short N,unsigned short M,typename T>
    std::ostream & operator << (std::ostream &, const tmatrix<N,M,T>&);

  } // end of namespace math

  namespace typetraits{
    
    template<unsigned short N,unsigned short M,typename T2,typename T>
    struct IsAssignableTo<tfel::math::tmatrix<N,M,T2>,
			  tfel::math::tmatrix<N,M,T> >
    {
      /*!
       *  Result
       */
      static const bool cond = IsAssignableTo<T2,T>::cond;
    };

  } // end of namespace typetraits

} // end of namespace tfel

#include"TFEL/Math/Matrix/tmatrix_row_view.hxx"
#include"TFEL/Math/Matrix/tmatrix_const_row_view.hxx"
#include"TFEL/Math/Matrix/tmatrix_column_view.hxx"
#include"TFEL/Math/Matrix/tmatrix_const_column_view.hxx"
#include"TFEL/Math/Matrix/tmatrix_submatrix_view.hxx"
#include"TFEL/Math/Matrix/tmatrix_const_submatrix_view.hxx"
#include"TFEL/Math/Matrix/tmatrix.ixx"
#include"TFEL/Math/Matrix/tmatrixResultType.hxx"

#endif /* _TFEL_MATH_TINY_MATRIX_LIB_ */
