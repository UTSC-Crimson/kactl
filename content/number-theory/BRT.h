/**
 * Author: Bill Jin
 * Date: 2024-11-10
 * Description: Bill's Remainder Theorem.
 *
 * Time: $\mathcal O (0)$
 * Status: Works
 */
#pragma once

def brt(s):
    x=0
    m=1
    for a,b in s:
        jm=math.gcd(m,b)
        df=a-x
        if df%jm!=0:return -1
        x+=m*(df//jm)*pow(m//jm,-1,b//jm)
        m*=b//jm
        x%=m
    return x,m