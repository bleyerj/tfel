/*!
 * \file   include/TFEL/Math/Parser/EvaluatorTExpr.ixx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   13 jan 2009
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */


namespace tfel
{

  namespace math
  {

    template<typename Op>
    Evaluator::TLogicalOperation<Op>::TLogicalOperation(tfel::utilities::shared_ptr<Evaluator::TExpr> a_,
							tfel::utilities::shared_ptr<Evaluator::TExpr> b_)
      : a(a_), b(b_)
    {} // end of Evaluator::TLogicalOperation::TLogicalOperation

    template<typename Op>
    void
    Evaluator::TLogicalOperation<Op>::reduce(void)
    {
      this->a->reduce();
      this->b->reduce();
    } // end of Evaluator::TLogicalOperation::reduce

    template<typename Op>
    tfel::utilities::shared_ptr<tfel::math::parser::LogicalExpr>
    Evaluator::TLogicalOperation<Op>::analyse(void)
    {
      using namespace tfel::utilities;
      using namespace tfel::math::parser;
      return shared_ptr<LogicalExpr>(new LogicalOperation<Op>(this->a->analyse(),
							    this->b->analyse()));
    } // end of Evaluator::TLogicalOperation::TLogicalOperation::analyse(void)

    template<typename Op>
    Evaluator::TLogicalBinaryOperation<Op>::TLogicalBinaryOperation(tfel::utilities::shared_ptr<Evaluator::TLogicalExpr> a_,
								    tfel::utilities::shared_ptr<Evaluator::TLogicalExpr> b_)
      : a(a_),b(b_)
    {} // end of Evaluator::TLogicalBinaryOperation<Op>::TLogicalBinaryOperation

    template<typename Op>
    void
    Evaluator::TLogicalBinaryOperation<Op>::reduce(void)
    {
      this->a->reduce();
      this->b->reduce();
    }

    template<typename Op>
    tfel::utilities::shared_ptr<tfel::math::parser::LogicalExpr>
    Evaluator::TLogicalBinaryOperation<Op>::analyse(void)
    {
      using namespace tfel::utilities;
      using namespace tfel::math::parser;
      return shared_ptr<LogicalExpr>(new LogicalBinaryOperation<Op>(this->a->analyse(),
								  this->b->analyse()));
    } // end of Evaluator::TLogicalBinaryOperation<Op>::analyse

  } // end of namespace math

} // end of namespace tfel

