//
// Created by Simone on 04/03/2022.
//

#pragma once


#ifdef ELOQUENT_NO_SINGLETON
#define ELOQUENT_SINGLETON(expr)
#else
#define ELOQUENT_SINGLETON(expr) expr;
#endif