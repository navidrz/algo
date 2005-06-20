/* TA-LIB Copyright (c) 1999-2004, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *  CF       Christo Fogelberg
 *
 * Change history:
 *
 *  MMDDYY BY     Description
 *  -------------------------------------------------------------------
 *  010802 MF     Template creation.
 *  052603 MF     Adapt code to compile with .NET Managed C++
 *  122104 MF,CF  Fix#1089506 for out-of-bound access to ep_temp.
 */

/* SAR_ROUNDING is just for test purpose when cross-referencing that
 * function with example from Wilder's book. Wilder is using two
 * decimal rounding for simplification. TA-Lib does not round.
 */
/* #define SAR_ROUNDING(x) x=round_pos_2(x) */
#define SAR_ROUNDING(x)

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #include "TA-Lib-Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (NAMESPACE(TA_RetCode)TA_INTERNAL_ERROR)
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */    #include "ta_trace.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::SAR_Lookback( double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                       double        optInMaximum )  /* From 0 to TA_REAL_MAX */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_SAR_Lookback( double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                    double        optInMaximum )  /* From 0 to TA_REAL_MAX */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   (void)optInAcceleration;
   (void)optInMaximum;

   /* SAR always sacrify one price bar to establish the
    * initial extreme price.
    */
   return 1;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_SAR - Parabolic SAR
 * 
 * Input  = High, Low
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInAcceleration:(From 0 to TA_REAL_MAX)
 *    Acceleration Factor used up to the Maximum value
 * 
 * optInMaximum:(From 0 to TA_REAL_MAX)
 *    Acceleration Factor Maximum value
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum class Core::TA_RetCode Core::SAR( int    startIdx,
/* Generated */                                        int    endIdx,
/* Generated */                                        cli::array<double>^ inHigh,
/* Generated */                                        cli::array<double>^ inLow,
/* Generated */                                        double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                                        double        optInMaximum, /* From 0 to TA_REAL_MAX */
/* Generated */                                        [OutAttribute]int^ outBegIdx,
/* Generated */                                        [OutAttribute]int^ outNbElement,
/* Generated */                                        cli::array<double>^  outReal )
/* Generated */ #else
/* Generated */ TA_RetCode TA_SAR( int    startIdx,
/* Generated */                    int    endIdx,
/* Generated */                    const double inHigh[],
/* Generated */                    const double inLow[],
/* Generated */                    double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                    double        optInMaximum, /* From 0 to TA_REAL_MAX */
/* Generated */                    int          *outBegIdx,
/* Generated */                    int          *outNbElement,
/* Generated */                    double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
	/* insert local variable here */
   TA_RetCode retCode;

   int isLong; /* > 0 indicates long. == 0 indicates short */
   int todayIdx, outIdx;

   VALUE_HANDLE(int,tempInt);

   double newHigh, newLow, prevHigh, prevLow;
   double af, ep, sar;
   ARRAY_LOCAL(ep_temp,1);

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh||!inLow)
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( optInAcceleration == TA_REAL_DEFAULT )
/* Generated */       optInAcceleration = 2.000000e-2;
/* Generated */    else if( (optInAcceleration < 0.000000e+0) ||/* Generated */  (optInAcceleration > 3.000000e+37) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( optInMaximum == TA_REAL_DEFAULT )
/* Generated */       optInMaximum = 2.000000e-1;
/* Generated */    else if( (optInMaximum < 0.000000e+0) ||/* Generated */  (optInMaximum > 3.000000e+37) )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( !outReal )
/* Generated */       return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Implementation of the SAR has been a little bit open to interpretation
    * since Wilder (the original author) did not define a precise algorithm
    * on how to bootstrap the algorithm. Take any existing software application
    * and you will see slight variation on how the algorithm was adapted.
    *
    * What is the initial trade direction? Long or short?
    * ===================================================
    * The interpretation of what should be the initial SAR values is
    * open to interpretation, particularly since the caller to the function
    * does not specify the initial direction of the trade.
    *
    * In TA-Lib, the following logic is used:
    *  - Calculate +DM and -DM between the first and
    *    second bar. The highest directional indication will
    *    indicate the assumed direction of the trade for the second
    *    price bar. 
    *  - In the case of a tigh between +DM and -DM,
    *    the direction is LONG by default.
    *
    * What is the initial "extreme point" and thus SAR?
    * =================================================
    * The following shows how different people took different approach:
    *  - Metastock use the first price bar high/low depending of
    *    the direction. No SAR is calculated for the first price
    *    bar.
    *  - Tradestation use the closing price of the second bar. No
    *    SAR are calculated for the first price bar.
    *  - Wilder (the original author) use the SIP from the
    *    previous trade (cannot be implement here since the
    *    direction and length of the previous trade is unknonw).
    *  - The Magazine TASC seems to follow Wilder approach which
    *    is not practical here.
    *
    * TA-Lib "consume" the first price bar and use its high/low as the
    * initial SAR of the second price bar. I found that approach to be
    * the closest to Wilders idea of having the first entry day use
    * the previous extreme point, except that here the extreme point is
    * derived solely from the first price bar. I found the same approach
    * to be used by Metastock.
    */

   /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    *
    * Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < 1 )
      startIdx = 1;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return NAMESPACE(TA_RetCode)TA_SUCCESS;
   }   

   /* Make sure the acceleration and maximum are coherent.
    * If not, correct the acceleration.
    */
   af = optInAcceleration;
   if( af > optInMaximum )
      af = optInAcceleration = optInMaximum;

   /* Identify if the initial direction is long or short.
    * (ep is just used as a temp buffer here, the name
    *  of the parameter is not significant).
    */
   retCode = TA_PREFIX(MINUS_DM)( startIdx, startIdx, inHigh, inLow, 1,
                                  VALUE_HANDLE_OUT(tempInt), VALUE_HANDLE_OUT(tempInt),
								  ep_temp );
   if( ep_temp[0] > 0 )
      isLong = 0;
   else
      isLong = 1;

   if( retCode != NAMESPACE(TA_RetCode)TA_SUCCESS )
   {
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
      return retCode;
   }

   VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
   outIdx = 0;

   /* Write the first SAR. */
   todayIdx = startIdx;

   newHigh = inHigh[todayIdx-1];
   newLow  = inLow[todayIdx-1];

   SAR_ROUNDING(newHigh);
   SAR_ROUNDING(newLow);

   if( isLong )
   {
      ep  = inHigh[todayIdx];
      sar = newLow;
   }
   else
   {
      ep  = inLow[todayIdx];
      sar = newHigh;
   }

   SAR_ROUNDING(sar);

   /* Cheat on the newLow and newHigh for the
    * first iteration.
    */
   newLow  = inLow[todayIdx];
   newHigh = inHigh[todayIdx];

   while( todayIdx <= endIdx )
   {
      prevLow  = newLow;
      prevHigh = newHigh;
      newLow  = inLow[todayIdx];
      newHigh = inHigh[todayIdx];   
      todayIdx++;

      SAR_ROUNDING(newLow);
      SAR_ROUNDING(newHigh);

      if( isLong )
      {  
         /* Switch to short if the low penetrates the SAR value. */
         if( newLow <= sar )
         {
            /* Switch and Overide the SAR with the ep */
            isLong = 0;
            sar = ep;

            /* Make sure the overide SAR is within
             * yesterday's and today's range.
             */
            if( sar < prevHigh )
               sar = prevHigh;            
            if( sar < newHigh )
               sar = newHigh;

            /* Output the overide SAR  */
            outReal[outIdx++] = sar;

            /* Adjust af and ep */
            af = optInAcceleration;
            ep = newLow;
 
            /* Calculate the new SAR */
            sar = sar + af * (ep - sar);
            SAR_ROUNDING( sar );

            /* Make sure the new SAR is within
             * yesterday's and today's range.
             */
            if( sar < prevHigh )
               sar = prevHigh;            
            if( sar < newHigh )
               sar = newHigh;
         }
         else
         {
            /* No switch */

            /* Output the SAR (was calculated in the previous iteration) */
            outReal[outIdx++] = sar;
 
            /* Adjust af and ep. */
            if( newHigh > ep )
            {
               ep = newHigh;
               af += optInAcceleration;
               if( af > optInMaximum )
                  af = optInMaximum;
            }

            /* Calculate the new SAR */
            sar = sar + af * (ep - sar);
            SAR_ROUNDING( sar );

            /* Make sure the new SAR is within
             * yesterday's and today's range.
             */
            if( sar > prevLow )
               sar = prevLow;            
            if( sar > newLow )
               sar = newLow;
         }
      }
      else
      {
         /* Switch to long if the high penetrates the SAR value. */
         if( newHigh >= sar )
         {
            /* Switch and Overide the SAR with the ep */
            isLong = 1;
            sar = ep;

            /* Make sure the overide SAR is within
             * yesterday's and today's range.
             */
            if( sar > prevLow )
               sar = prevLow;            
            if( sar > newLow )
               sar = newLow;

            /* Output the overide SAR  */
            outReal[outIdx++] = sar;

            /* Adjust af and ep */
            af = optInAcceleration;
            ep = newHigh;

            /* Calculate the new SAR */
            sar = sar + af * (ep - sar);
            SAR_ROUNDING( sar );

            /* Make sure the new SAR is within
             * yesterday's and today's range.
             */
            if( sar > prevLow )
               sar = prevLow;            
            if( sar > newLow )
               sar = newLow;
         }
         else
         {
            /* No switch */

            /* Output the SAR (was calculated in the previous iteration) */
            outReal[outIdx++] = sar;

            /* Adjust af and ep. */
            if( newLow < ep )
            {
               ep = newLow;
               af += optInAcceleration;
               if( af > optInMaximum )
                  af = optInMaximum;
            }

            /* Calculate the new SAR */
            sar = sar + af * (ep - sar);
            SAR_ROUNDING( sar );

            /* Make sure the new SAR is within
             * yesterday's and today's range.
             */
            if( sar < prevHigh )
               sar = prevHigh;            
            if( sar < newHigh )
               sar = newHigh;
         }
      }
   }

   VALUE_HANDLE_DEREF(outNbElement) = outIdx;

   return NAMESPACE(TA_RetCode)TA_SUCCESS;
}

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum class Core::TA_RetCode Core::SAR( int    startIdx,
/* Generated */                                        int    endIdx,
/* Generated */                                        cli::array<float>^ inHigh,
/* Generated */                                        cli::array<float>^ inLow,
/* Generated */                                        double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                                        double        optInMaximum, /* From 0 to TA_REAL_MAX */
/* Generated */                                        [OutAttribute]int^ outBegIdx,
/* Generated */                                        [OutAttribute]int^ outNbElement,
/* Generated */                                        cli::array<double>^  outReal )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_SAR( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      const float  inHigh[],
/* Generated */                      const float  inLow[],
/* Generated */                      double        optInAcceleration, /* From 0 to TA_REAL_MAX */
/* Generated */                      double        optInMaximum, /* From 0 to TA_REAL_MAX */
/* Generated */                      int          *outBegIdx,
/* Generated */                      int          *outNbElement,
/* Generated */                      double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    TA_RetCode retCode;
/* Generated */    int isLong; 
/* Generated */    int todayIdx, outIdx;
/* Generated */    VALUE_HANDLE(int,tempInt);
/* Generated */    double newHigh, newLow, prevHigh, prevLow;
/* Generated */    double af, ep, sar;
/* Generated */    ARRAY_LOCAL(ep_temp,1);
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return NAMESPACE(TA_RetCode)TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if(!inHigh||!inLow)
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( optInAcceleration == TA_REAL_DEFAULT )
/* Generated */        optInAcceleration = 2.000000e-2;
/* Generated */     else if( (optInAcceleration < 0.000000e+0) ||  (optInAcceleration > 3.000000e+37) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( optInMaximum == TA_REAL_DEFAULT )
/* Generated */        optInMaximum = 2.000000e-1;
/* Generated */     else if( (optInMaximum < 0.000000e+0) ||  (optInMaximum > 3.000000e+37) )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */     if( !outReal )
/* Generated */        return NAMESPACE(TA_RetCode)TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    if( startIdx < 1 )
/* Generated */       startIdx = 1;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */    }   
/* Generated */    af = optInAcceleration;
/* Generated */    if( af > optInMaximum )
/* Generated */       af = optInAcceleration = optInMaximum;
/* Generated */    retCode = TA_PREFIX(MINUS_DM)( startIdx, startIdx, inHigh, inLow, 1,
/* Generated */                                   VALUE_HANDLE_OUT(tempInt), VALUE_HANDLE_OUT(tempInt),
/* Generated */ 								  ep_temp );
/* Generated */    if( ep_temp[0] > 0 )
/* Generated */       isLong = 0;
/* Generated */    else
/* Generated */       isLong = 1;
/* Generated */    if( retCode != NAMESPACE(TA_RetCode)TA_SUCCESS )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNbElement);
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx) = startIdx;
/* Generated */    outIdx = 0;
/* Generated */    todayIdx = startIdx;
/* Generated */    newHigh = inHigh[todayIdx-1];
/* Generated */    newLow  = inLow[todayIdx-1];
/* Generated */    SAR_ROUNDING(newHigh);
/* Generated */    SAR_ROUNDING(newLow);
/* Generated */    if( isLong )
/* Generated */    {
/* Generated */       ep  = inHigh[todayIdx];
/* Generated */       sar = newLow;
/* Generated */    }
/* Generated */    else
/* Generated */    {
/* Generated */       ep  = inLow[todayIdx];
/* Generated */       sar = newHigh;
/* Generated */    }
/* Generated */    SAR_ROUNDING(sar);
/* Generated */    newLow  = inLow[todayIdx];
/* Generated */    newHigh = inHigh[todayIdx];
/* Generated */    while( todayIdx <= endIdx )
/* Generated */    {
/* Generated */       prevLow  = newLow;
/* Generated */       prevHigh = newHigh;
/* Generated */       newLow  = inLow[todayIdx];
/* Generated */       newHigh = inHigh[todayIdx];   
/* Generated */       todayIdx++;
/* Generated */       SAR_ROUNDING(newLow);
/* Generated */       SAR_ROUNDING(newHigh);
/* Generated */       if( isLong )
/* Generated */       {  
/* Generated */          if( newLow <= sar )
/* Generated */          {
/* Generated */             isLong = 0;
/* Generated */             sar = ep;
/* Generated */             if( sar < prevHigh )
/* Generated */                sar = prevHigh;            
/* Generated */             if( sar < newHigh )
/* Generated */                sar = newHigh;
/* Generated */             outReal[outIdx++] = sar;
/* Generated */             af = optInAcceleration;
/* Generated */             ep = newLow;
/* Generated */             sar = sar + af * (ep - sar);
/* Generated */             SAR_ROUNDING( sar );
/* Generated */             if( sar < prevHigh )
/* Generated */                sar = prevHigh;            
/* Generated */             if( sar < newHigh )
/* Generated */                sar = newHigh;
/* Generated */          }
/* Generated */          else
/* Generated */          {
/* Generated */             outReal[outIdx++] = sar;
/* Generated */             if( newHigh > ep )
/* Generated */             {
/* Generated */                ep = newHigh;
/* Generated */                af += optInAcceleration;
/* Generated */                if( af > optInMaximum )
/* Generated */                   af = optInMaximum;
/* Generated */             }
/* Generated */             sar = sar + af * (ep - sar);
/* Generated */             SAR_ROUNDING( sar );
/* Generated */             if( sar > prevLow )
/* Generated */                sar = prevLow;            
/* Generated */             if( sar > newLow )
/* Generated */                sar = newLow;
/* Generated */          }
/* Generated */       }
/* Generated */       else
/* Generated */       {
/* Generated */          if( newHigh >= sar )
/* Generated */          {
/* Generated */             isLong = 1;
/* Generated */             sar = ep;
/* Generated */             if( sar > prevLow )
/* Generated */                sar = prevLow;            
/* Generated */             if( sar > newLow )
/* Generated */                sar = newLow;
/* Generated */             outReal[outIdx++] = sar;
/* Generated */             af = optInAcceleration;
/* Generated */             ep = newHigh;
/* Generated */             sar = sar + af * (ep - sar);
/* Generated */             SAR_ROUNDING( sar );
/* Generated */             if( sar > prevLow )
/* Generated */                sar = prevLow;            
/* Generated */             if( sar > newLow )
/* Generated */                sar = newLow;
/* Generated */          }
/* Generated */          else
/* Generated */          {
/* Generated */             outReal[outIdx++] = sar;
/* Generated */             if( newLow < ep )
/* Generated */             {
/* Generated */                ep = newLow;
/* Generated */                af += optInAcceleration;
/* Generated */                if( af > optInMaximum )
/* Generated */                   af = optInMaximum;
/* Generated */             }
/* Generated */             sar = sar + af * (ep - sar);
/* Generated */             SAR_ROUNDING( sar );
/* Generated */             if( sar < prevHigh )
/* Generated */                sar = prevHigh;            
/* Generated */             if( sar < newHigh )
/* Generated */                sar = newHigh;
/* Generated */          }
/* Generated */       }
/* Generated */    }
/* Generated */    VALUE_HANDLE_DEREF(outNbElement) = outIdx;
/* Generated */    return NAMESPACE(TA_RetCode)TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

