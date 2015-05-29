#include "station.h"

DiscountRecord 
Station::discount_table = {
	{Electric, 30, 40},
	{Lady, 25, 30},
	{Road, 15, 20},
	{Hybrid, 20, 25}
};

