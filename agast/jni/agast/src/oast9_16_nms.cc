//
//    oast9 - OAST, an optimal corner detector based on the
//              accelerated segment test for a 16 pixel mask
//
//    Copyright (C) 2010  Elmar Mair
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>
#include <stdlib.h>
#include <agast/cvWrapper.h>
#include <agast/oast9_16.h>

using namespace std;
using namespace agast;

//using also bisection as propsed by Edward Rosten in FAST,
//but it is based on the OAST
int OastDetector9_16::cornerScore(const unsigned char* p)
{
    int bmin = b;
    //std::cout <<int(b)<<":";
    int bmax = 255;
    int b_test = (bmax + bmin)/2;

	register int_fast16_t offset0=s_offset0;
	register int_fast16_t offset1=s_offset1;
	register int_fast16_t offset2=s_offset2;
	register int_fast16_t offset3=s_offset3;
	register int_fast16_t offset4=s_offset4;
	register int_fast16_t offset5=s_offset5;
	register int_fast16_t offset6=s_offset6;
	register int_fast16_t offset7=s_offset7;
	register int_fast16_t offset8=s_offset8;
	register int_fast16_t offset9=s_offset9;
	register int_fast16_t offset10=s_offset10;
	register int_fast16_t offset11=s_offset11;
	register int_fast16_t offset12=s_offset12;
	register int_fast16_t offset13=s_offset13;
	register int_fast16_t offset14=s_offset14;
	register int_fast16_t offset15=s_offset15;

	while(1)
	{
		register const int cb = *p + b_test;
		//std::cout << offset0 << ".";
		register const int c_b = *p - b_test;
		if(p[offset0] > cb)
		  if(p[offset2] > cb)
		    if(p[offset4] > cb)
		      if(p[offset5] > cb)
		        if(p[offset7] > cb)
		          if(p[offset3] > cb)
		            if(p[offset1] > cb)
		              if(p[offset6] > cb)
		                if(p[offset8] > cb)
		                  goto is_a_corner;
		                else
		                  if(p[offset15] > cb)
		                    goto is_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset13] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset8] > cb)
		                if(p[offset9] > cb)
		                  if(p[offset10] > cb)
		                    if(p[offset6] > cb)
		                      goto is_a_corner;
		                    else
		                      if(p[offset11] > cb)
		                        if(p[offset12] > cb)
		                          if(p[offset13] > cb)
		                            if(p[offset14] > cb)
		                              if(p[offset15] > cb)
		                                goto is_a_corner;
		                              else
		                                goto is_not_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] > cb)
		              if(p[offset11] > cb)
		                if(p[offset12] > cb)
		                  if(p[offset8] > cb)
		                    if(p[offset9] > cb)
		                      if(p[offset6] > cb)
		                        goto is_a_corner;
		                      else
		                        if(p[offset13] > cb)
		                          if(p[offset14] > cb)
		                            if(p[offset15] > cb)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(p[offset1] > cb)
		                        if(p[offset13] > cb)
		                          if(p[offset14] > cb)
		                            if(p[offset15] > cb)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset1] > cb)
		                      if(p[offset13] > cb)
		                        if(p[offset14] > cb)
		                          if(p[offset15] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else if(p[offset7] < c_b)
		          if(p[offset14] > cb)
		            if(p[offset15] > cb)
		              if(p[offset1] > cb)
		                if(p[offset3] > cb)
		                  if(p[offset6] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset13] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] > cb)
		                    if(p[offset11] > cb)
		                      if(p[offset12] > cb)
		                        if(p[offset13] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset8] > cb)
		                  if(p[offset9] > cb)
		                    if(p[offset10] > cb)
		                      if(p[offset11] > cb)
		                        if(p[offset12] > cb)
		                          if(p[offset13] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else if(p[offset14] < c_b)
		            if(p[offset8] < c_b)
		              if(p[offset9] < c_b)
		                if(p[offset10] < c_b)
		                  if(p[offset11] < c_b)
		                    if(p[offset12] < c_b)
		                      if(p[offset13] < c_b)
		                        if(p[offset6] < c_b)
		                          goto is_a_corner;
		                        else
		                          if(p[offset15] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          if(p[offset14] > cb)
		            if(p[offset15] > cb)
		              if(p[offset1] > cb)
		                if(p[offset3] > cb)
		                  if(p[offset6] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset13] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] > cb)
		                    if(p[offset11] > cb)
		                      if(p[offset12] > cb)
		                        if(p[offset13] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset8] > cb)
		                  if(p[offset9] > cb)
		                    if(p[offset10] > cb)
		                      if(p[offset11] > cb)
		                        if(p[offset12] > cb)
		                          if(p[offset13] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else if(p[offset5] < c_b)
		        if(p[offset12] > cb)
		          if(p[offset13] > cb)
		            if(p[offset14] > cb)
		              if(p[offset15] > cb)
		                if(p[offset1] > cb)
		                  if(p[offset3] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] > cb)
		                      if(p[offset11] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset8] > cb)
		                    if(p[offset9] > cb)
		                      if(p[offset10] > cb)
		                        if(p[offset11] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset6] > cb)
		                  if(p[offset7] > cb)
		                    if(p[offset8] > cb)
		                      if(p[offset9] > cb)
		                        if(p[offset10] > cb)
		                          if(p[offset11] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(p[offset12] < c_b)
		          if(p[offset7] < c_b)
		            if(p[offset8] < c_b)
		              if(p[offset9] < c_b)
		                if(p[offset10] < c_b)
		                  if(p[offset11] < c_b)
		                    if(p[offset13] < c_b)
		                      if(p[offset6] < c_b)
		                        goto is_a_corner;
		                      else
		                        if(p[offset14] < c_b)
		                          if(p[offset15] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        if(p[offset12] > cb)
		          if(p[offset13] > cb)
		            if(p[offset14] > cb)
		              if(p[offset15] > cb)
		                if(p[offset1] > cb)
		                  if(p[offset3] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] > cb)
		                      if(p[offset11] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset8] > cb)
		                    if(p[offset9] > cb)
		                      if(p[offset10] > cb)
		                        if(p[offset11] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset6] > cb)
		                  if(p[offset7] > cb)
		                    if(p[offset8] > cb)
		                      if(p[offset9] > cb)
		                        if(p[offset10] > cb)
		                          if(p[offset11] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(p[offset12] < c_b)
		          if(p[offset7] < c_b)
		            if(p[offset8] < c_b)
		              if(p[offset9] < c_b)
		                if(p[offset10] < c_b)
		                  if(p[offset11] < c_b)
		                    if(p[offset13] < c_b)
		                      if(p[offset14] < c_b)
		                        if(p[offset6] < c_b)
		                          goto is_a_corner;
		                        else
		                          if(p[offset15] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		    else if(p[offset4] < c_b)
		      if(p[offset11] > cb)
		        if(p[offset12] > cb)
		          if(p[offset13] > cb)
		            if(p[offset10] > cb)
		              if(p[offset14] > cb)
		                if(p[offset15] > cb)
		                  if(p[offset1] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset8] > cb)
		                      if(p[offset9] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset6] > cb)
		                    if(p[offset7] > cb)
		                      if(p[offset8] > cb)
		                        if(p[offset9] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset5] > cb)
		                  if(p[offset6] > cb)
		                    if(p[offset7] > cb)
		                      if(p[offset8] > cb)
		                        if(p[offset9] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset1] > cb)
		                if(p[offset3] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(p[offset11] < c_b)
		        if(p[offset7] < c_b)
		          if(p[offset8] < c_b)
		            if(p[offset9] < c_b)
		              if(p[offset10] < c_b)
		                if(p[offset6] < c_b)
		                  if(p[offset5] < c_b)
		                    if(p[offset3] < c_b)
		                      goto is_a_corner;
		                    else
		                      if(p[offset12] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset12] < c_b)
		                      if(p[offset13] < c_b)
		                        if(p[offset14] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset12] < c_b)
		                    if(p[offset13] < c_b)
		                      if(p[offset14] < c_b)
		                        if(p[offset15] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      if(p[offset11] > cb)
		        if(p[offset12] > cb)
		          if(p[offset13] > cb)
		            if(p[offset10] > cb)
		              if(p[offset14] > cb)
		                if(p[offset15] > cb)
		                  if(p[offset1] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset8] > cb)
		                      if(p[offset9] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset6] > cb)
		                    if(p[offset7] > cb)
		                      if(p[offset8] > cb)
		                        if(p[offset9] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset5] > cb)
		                  if(p[offset6] > cb)
		                    if(p[offset7] > cb)
		                      if(p[offset8] > cb)
		                        if(p[offset9] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset1] > cb)
		                if(p[offset3] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(p[offset11] < c_b)
		        if(p[offset7] < c_b)
		          if(p[offset8] < c_b)
		            if(p[offset9] < c_b)
		              if(p[offset10] < c_b)
		                if(p[offset12] < c_b)
		                  if(p[offset13] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset5] < c_b)
		                        goto is_a_corner;
		                      else
		                        if(p[offset14] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(p[offset14] < c_b)
		                        if(p[offset15] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		  else if(p[offset2] < c_b)
		    if(p[offset9] > cb)
		      if(p[offset10] > cb)
		        if(p[offset11] > cb)
		          if(p[offset8] > cb)
		            if(p[offset12] > cb)
		              if(p[offset13] > cb)
		                if(p[offset14] > cb)
		                  if(p[offset15] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset4] > cb)
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset3] > cb)
		                if(p[offset4] > cb)
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset1] > cb)
		              if(p[offset12] > cb)
		                if(p[offset13] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(p[offset9] < c_b)
		      if(p[offset7] < c_b)
		        if(p[offset8] < c_b)
		          if(p[offset6] < c_b)
		            if(p[offset5] < c_b)
		              if(p[offset4] < c_b)
		                if(p[offset3] < c_b)
		                  if(p[offset1] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] < c_b)
		                    if(p[offset11] < c_b)
		                      if(p[offset12] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset10] < c_b)
		                  if(p[offset11] < c_b)
		                    if(p[offset12] < c_b)
		                      if(p[offset13] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset10] < c_b)
		                if(p[offset11] < c_b)
		                  if(p[offset12] < c_b)
		                    if(p[offset13] < c_b)
		                      if(p[offset14] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] < c_b)
		              if(p[offset11] < c_b)
		                if(p[offset12] < c_b)
		                  if(p[offset13] < c_b)
		                    if(p[offset14] < c_b)
		                      if(p[offset15] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else
		    if(p[offset9] > cb)
		      if(p[offset10] > cb)
		        if(p[offset11] > cb)
		          if(p[offset8] > cb)
		            if(p[offset12] > cb)
		              if(p[offset13] > cb)
		                if(p[offset14] > cb)
		                  if(p[offset15] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset4] > cb)
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset3] > cb)
		                if(p[offset4] > cb)
		                  if(p[offset5] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset7] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset1] > cb)
		              if(p[offset12] > cb)
		                if(p[offset13] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(p[offset9] < c_b)
		      if(p[offset7] < c_b)
		        if(p[offset8] < c_b)
		          if(p[offset10] < c_b)
		            if(p[offset11] < c_b)
		              if(p[offset6] < c_b)
		                if(p[offset5] < c_b)
		                  if(p[offset4] < c_b)
		                    if(p[offset3] < c_b)
		                      goto is_a_corner;
		                    else
		                      if(p[offset12] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset12] < c_b)
		                      if(p[offset13] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset12] < c_b)
		                    if(p[offset13] < c_b)
		                      if(p[offset14] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset12] < c_b)
		                  if(p[offset13] < c_b)
		                    if(p[offset14] < c_b)
		                      if(p[offset15] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		else if(p[offset0] < c_b)
		  if(p[offset2] > cb)
		    if(p[offset9] > cb)
		      if(p[offset7] > cb)
		        if(p[offset8] > cb)
		          if(p[offset6] > cb)
		            if(p[offset5] > cb)
		              if(p[offset4] > cb)
		                if(p[offset3] > cb)
		                  if(p[offset1] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] > cb)
		                    if(p[offset11] > cb)
		                      if(p[offset12] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset10] > cb)
		                  if(p[offset11] > cb)
		                    if(p[offset12] > cb)
		                      if(p[offset13] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset10] > cb)
		                if(p[offset11] > cb)
		                  if(p[offset12] > cb)
		                    if(p[offset13] > cb)
		                      if(p[offset14] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] > cb)
		              if(p[offset11] > cb)
		                if(p[offset12] > cb)
		                  if(p[offset13] > cb)
		                    if(p[offset14] > cb)
		                      if(p[offset15] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(p[offset9] < c_b)
		      if(p[offset10] < c_b)
		        if(p[offset11] < c_b)
		          if(p[offset8] < c_b)
		            if(p[offset12] < c_b)
		              if(p[offset13] < c_b)
		                if(p[offset14] < c_b)
		                  if(p[offset15] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset4] < c_b)
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset3] < c_b)
		                if(p[offset4] < c_b)
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset1] < c_b)
		              if(p[offset12] < c_b)
		                if(p[offset13] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else if(p[offset2] < c_b)
		    if(p[offset4] > cb)
		      if(p[offset11] > cb)
		        if(p[offset7] > cb)
		          if(p[offset8] > cb)
		            if(p[offset9] > cb)
		              if(p[offset10] > cb)
		                if(p[offset6] > cb)
		                  if(p[offset5] > cb)
		                    if(p[offset3] > cb)
		                      goto is_a_corner;
		                    else
		                      if(p[offset12] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset12] > cb)
		                      if(p[offset13] > cb)
		                        if(p[offset14] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset12] > cb)
		                    if(p[offset13] > cb)
		                      if(p[offset14] > cb)
		                        if(p[offset15] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(p[offset11] < c_b)
		        if(p[offset12] < c_b)
		          if(p[offset13] < c_b)
		            if(p[offset10] < c_b)
		              if(p[offset14] < c_b)
		                if(p[offset15] < c_b)
		                  if(p[offset1] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset8] < c_b)
		                      if(p[offset9] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset6] < c_b)
		                    if(p[offset7] < c_b)
		                      if(p[offset8] < c_b)
		                        if(p[offset9] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset5] < c_b)
		                  if(p[offset6] < c_b)
		                    if(p[offset7] < c_b)
		                      if(p[offset8] < c_b)
		                        if(p[offset9] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset1] < c_b)
		                if(p[offset3] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(p[offset4] < c_b)
		      if(p[offset5] > cb)
		        if(p[offset12] > cb)
		          if(p[offset7] > cb)
		            if(p[offset8] > cb)
		              if(p[offset9] > cb)
		                if(p[offset10] > cb)
		                  if(p[offset11] > cb)
		                    if(p[offset13] > cb)
		                      if(p[offset6] > cb)
		                        goto is_a_corner;
		                      else
		                        if(p[offset14] > cb)
		                          if(p[offset15] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(p[offset12] < c_b)
		          if(p[offset13] < c_b)
		            if(p[offset14] < c_b)
		              if(p[offset15] < c_b)
		                if(p[offset1] < c_b)
		                  if(p[offset3] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] < c_b)
		                      if(p[offset11] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset8] < c_b)
		                    if(p[offset9] < c_b)
		                      if(p[offset10] < c_b)
		                        if(p[offset11] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset6] < c_b)
		                  if(p[offset7] < c_b)
		                    if(p[offset8] < c_b)
		                      if(p[offset9] < c_b)
		                        if(p[offset10] < c_b)
		                          if(p[offset11] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(p[offset5] < c_b)
		        if(p[offset7] > cb)
		          if(p[offset14] > cb)
		            if(p[offset8] > cb)
		              if(p[offset9] > cb)
		                if(p[offset10] > cb)
		                  if(p[offset11] > cb)
		                    if(p[offset12] > cb)
		                      if(p[offset13] > cb)
		                        if(p[offset6] > cb)
		                          goto is_a_corner;
		                        else
		                          if(p[offset15] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else if(p[offset14] < c_b)
		            if(p[offset15] < c_b)
		              if(p[offset1] < c_b)
		                if(p[offset3] < c_b)
		                  if(p[offset6] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset13] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] < c_b)
		                    if(p[offset11] < c_b)
		                      if(p[offset12] < c_b)
		                        if(p[offset13] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset8] < c_b)
		                  if(p[offset9] < c_b)
		                    if(p[offset10] < c_b)
		                      if(p[offset11] < c_b)
		                        if(p[offset12] < c_b)
		                          if(p[offset13] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(p[offset7] < c_b)
		          if(p[offset3] < c_b)
		            if(p[offset1] < c_b)
		              if(p[offset6] < c_b)
		                if(p[offset8] < c_b)
		                  goto is_a_corner;
		                else
		                  if(p[offset15] < c_b)
		                    goto is_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset13] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset8] < c_b)
		                if(p[offset9] < c_b)
		                  if(p[offset10] < c_b)
		                    if(p[offset6] < c_b)
		                      goto is_a_corner;
		                    else
		                      if(p[offset11] < c_b)
		                        if(p[offset12] < c_b)
		                          if(p[offset13] < c_b)
		                            if(p[offset14] < c_b)
		                              if(p[offset15] < c_b)
		                                goto is_a_corner;
		                              else
		                                goto is_not_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] < c_b)
		              if(p[offset11] < c_b)
		                if(p[offset12] < c_b)
		                  if(p[offset8] < c_b)
		                    if(p[offset9] < c_b)
		                      if(p[offset6] < c_b)
		                        goto is_a_corner;
		                      else
		                        if(p[offset13] < c_b)
		                          if(p[offset14] < c_b)
		                            if(p[offset15] < c_b)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(p[offset1] < c_b)
		                        if(p[offset13] < c_b)
		                          if(p[offset14] < c_b)
		                            if(p[offset15] < c_b)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset1] < c_b)
		                      if(p[offset13] < c_b)
		                        if(p[offset14] < c_b)
		                          if(p[offset15] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(p[offset14] < c_b)
		            if(p[offset15] < c_b)
		              if(p[offset1] < c_b)
		                if(p[offset3] < c_b)
		                  if(p[offset6] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset13] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] < c_b)
		                    if(p[offset11] < c_b)
		                      if(p[offset12] < c_b)
		                        if(p[offset13] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset8] < c_b)
		                  if(p[offset9] < c_b)
		                    if(p[offset10] < c_b)
		                      if(p[offset11] < c_b)
		                        if(p[offset12] < c_b)
		                          if(p[offset13] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        if(p[offset12] > cb)
		          if(p[offset7] > cb)
		            if(p[offset8] > cb)
		              if(p[offset9] > cb)
		                if(p[offset10] > cb)
		                  if(p[offset11] > cb)
		                    if(p[offset13] > cb)
		                      if(p[offset14] > cb)
		                        if(p[offset6] > cb)
		                          goto is_a_corner;
		                        else
		                          if(p[offset15] > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(p[offset12] < c_b)
		          if(p[offset13] < c_b)
		            if(p[offset14] < c_b)
		              if(p[offset15] < c_b)
		                if(p[offset1] < c_b)
		                  if(p[offset3] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] < c_b)
		                      if(p[offset11] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset8] < c_b)
		                    if(p[offset9] < c_b)
		                      if(p[offset10] < c_b)
		                        if(p[offset11] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset6] < c_b)
		                  if(p[offset7] < c_b)
		                    if(p[offset8] < c_b)
		                      if(p[offset9] < c_b)
		                        if(p[offset10] < c_b)
		                          if(p[offset11] < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		    else
		      if(p[offset11] > cb)
		        if(p[offset7] > cb)
		          if(p[offset8] > cb)
		            if(p[offset9] > cb)
		              if(p[offset10] > cb)
		                if(p[offset12] > cb)
		                  if(p[offset13] > cb)
		                    if(p[offset6] > cb)
		                      if(p[offset5] > cb)
		                        goto is_a_corner;
		                      else
		                        if(p[offset14] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(p[offset14] > cb)
		                        if(p[offset15] > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(p[offset11] < c_b)
		        if(p[offset12] < c_b)
		          if(p[offset13] < c_b)
		            if(p[offset10] < c_b)
		              if(p[offset14] < c_b)
		                if(p[offset15] < c_b)
		                  if(p[offset1] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset8] < c_b)
		                      if(p[offset9] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset6] < c_b)
		                    if(p[offset7] < c_b)
		                      if(p[offset8] < c_b)
		                        if(p[offset9] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset5] < c_b)
		                  if(p[offset6] < c_b)
		                    if(p[offset7] < c_b)
		                      if(p[offset8] < c_b)
		                        if(p[offset9] < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset1] < c_b)
		                if(p[offset3] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		  else
		    if(p[offset9] > cb)
		      if(p[offset7] > cb)
		        if(p[offset8] > cb)
		          if(p[offset10] > cb)
		            if(p[offset11] > cb)
		              if(p[offset6] > cb)
		                if(p[offset5] > cb)
		                  if(p[offset4] > cb)
		                    if(p[offset3] > cb)
		                      goto is_a_corner;
		                    else
		                      if(p[offset12] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(p[offset12] > cb)
		                      if(p[offset13] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset12] > cb)
		                    if(p[offset13] > cb)
		                      if(p[offset14] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset12] > cb)
		                  if(p[offset13] > cb)
		                    if(p[offset14] > cb)
		                      if(p[offset15] > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(p[offset9] < c_b)
		      if(p[offset10] < c_b)
		        if(p[offset11] < c_b)
		          if(p[offset8] < c_b)
		            if(p[offset12] < c_b)
		              if(p[offset13] < c_b)
		                if(p[offset14] < c_b)
		                  if(p[offset15] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset4] < c_b)
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset3] < c_b)
		                if(p[offset4] < c_b)
		                  if(p[offset5] < c_b)
		                    if(p[offset6] < c_b)
		                      if(p[offset7] < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset1] < c_b)
		              if(p[offset12] < c_b)
		                if(p[offset13] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		else
		  if(p[offset7] > cb)
		    if(p[offset8] > cb)
		      if(p[offset9] > cb)
		        if(p[offset6] > cb)
		          if(p[offset5] > cb)
		            if(p[offset4] > cb)
		              if(p[offset3] > cb)
		                if(p[offset2] > cb)
		                  if(p[offset1] > cb)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] > cb)
		                    if(p[offset11] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset10] > cb)
		                  if(p[offset11] > cb)
		                    if(p[offset12] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset10] > cb)
		                if(p[offset11] > cb)
		                  if(p[offset12] > cb)
		                    if(p[offset13] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] > cb)
		              if(p[offset11] > cb)
		                if(p[offset12] > cb)
		                  if(p[offset13] > cb)
		                    if(p[offset14] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(p[offset10] > cb)
		            if(p[offset11] > cb)
		              if(p[offset12] > cb)
		                if(p[offset13] > cb)
		                  if(p[offset14] > cb)
		                    if(p[offset15] > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else if(p[offset7] < c_b)
		    if(p[offset8] < c_b)
		      if(p[offset9] < c_b)
		        if(p[offset6] < c_b)
		          if(p[offset5] < c_b)
		            if(p[offset4] < c_b)
		              if(p[offset3] < c_b)
		                if(p[offset2] < c_b)
		                  if(p[offset1] < c_b)
		                    goto is_a_corner;
		                  else
		                    if(p[offset10] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(p[offset10] < c_b)
		                    if(p[offset11] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(p[offset10] < c_b)
		                  if(p[offset11] < c_b)
		                    if(p[offset12] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(p[offset10] < c_b)
		                if(p[offset11] < c_b)
		                  if(p[offset12] < c_b)
		                    if(p[offset13] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(p[offset10] < c_b)
		              if(p[offset11] < c_b)
		                if(p[offset12] < c_b)
		                  if(p[offset13] < c_b)
		                    if(p[offset14] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(p[offset10] < c_b)
		            if(p[offset11] < c_b)
		              if(p[offset12] < c_b)
		                if(p[offset13] < c_b)
		                  if(p[offset14] < c_b)
		                    if(p[offset15] < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else
		    goto is_not_a_corner;

		is_a_corner:
			bmin=b_test;
			goto end;

		is_not_a_corner:
			bmax=b_test;
			goto end;

		end:

		if(bmin == bmax - 1 || bmin == bmax)
			return bmin;
		b_test = (bmin + bmax) / 2;
	}
}

int OastDetector9_16::cornerScore(cv::Mat& img, float x, float y, float scale)
{
	// check boundary
	if(floor(x-3.5*scale)<0) return 0;
	if(floor(y-3.5*scale)<0) return 0;
	if(ceil(x+3.5*scale)>=img.cols) return 0;
	if(ceil(y+3.5*scale)>=img.cols) return 0;

    int bmin = b;
    //std::cout <<int(b)<<":";
    int bmax = 255;
    int b_test = (bmax + bmin)/2;

    Oast9_16_PatternAccessor accessor(img);
    accessor.setCenter(x,y,scale);

	while(1)
	{
		register const int cb = accessor(16) + b_test;
		//std::cout << offset0 << ".";
		register const int c_b = cb - 2*b_test;
		if(accessor(0) > cb)
		  if(accessor(2) > cb)
		    if(accessor(4) > cb)
		      if(accessor(5) > cb)
		        if(accessor(7) > cb)
		          if(accessor(3) > cb)
		            if(accessor(1) > cb)
		              if(accessor(6) > cb)
		                if(accessor(8) > cb)
		                  goto is_a_corner;
		                else
		                  if(accessor(15) > cb)
		                    goto is_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(13) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(8) > cb)
		                if(accessor(9) > cb)
		                  if(accessor(10) > cb)
		                    if(accessor(6) > cb)
		                      goto is_a_corner;
		                    else
		                      if(accessor(11) > cb)
		                        if(accessor(12) > cb)
		                          if(accessor(13) > cb)
		                            if(accessor(14) > cb)
		                              if(accessor(15) > cb)
		                                goto is_a_corner;
		                              else
		                                goto is_not_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) > cb)
		              if(accessor(11) > cb)
		                if(accessor(12) > cb)
		                  if(accessor(8) > cb)
		                    if(accessor(9) > cb)
		                      if(accessor(6) > cb)
		                        goto is_a_corner;
		                      else
		                        if(accessor(13) > cb)
		                          if(accessor(14) > cb)
		                            if(accessor(15) > cb)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(accessor(1) > cb)
		                        if(accessor(13) > cb)
		                          if(accessor(14) > cb)
		                            if(accessor(15) > cb)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(1) > cb)
		                      if(accessor(13) > cb)
		                        if(accessor(14) > cb)
		                          if(accessor(15) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else if(accessor(7) < c_b)
		          if(accessor(14) > cb)
		            if(accessor(15) > cb)
		              if(accessor(1) > cb)
		                if(accessor(3) > cb)
		                  if(accessor(6) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(13) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) > cb)
		                    if(accessor(11) > cb)
		                      if(accessor(12) > cb)
		                        if(accessor(13) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(8) > cb)
		                  if(accessor(9) > cb)
		                    if(accessor(10) > cb)
		                      if(accessor(11) > cb)
		                        if(accessor(12) > cb)
		                          if(accessor(13) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else if(accessor(14) < c_b)
		            if(accessor(8) < c_b)
		              if(accessor(9) < c_b)
		                if(accessor(10) < c_b)
		                  if(accessor(11) < c_b)
		                    if(accessor(12) < c_b)
		                      if(accessor(13) < c_b)
		                        if(accessor(6) < c_b)
		                          goto is_a_corner;
		                        else
		                          if(accessor(15) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          if(accessor(14) > cb)
		            if(accessor(15) > cb)
		              if(accessor(1) > cb)
		                if(accessor(3) > cb)
		                  if(accessor(6) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(13) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) > cb)
		                    if(accessor(11) > cb)
		                      if(accessor(12) > cb)
		                        if(accessor(13) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(8) > cb)
		                  if(accessor(9) > cb)
		                    if(accessor(10) > cb)
		                      if(accessor(11) > cb)
		                        if(accessor(12) > cb)
		                          if(accessor(13) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else if(accessor(5) < c_b)
		        if(accessor(12) > cb)
		          if(accessor(13) > cb)
		            if(accessor(14) > cb)
		              if(accessor(15) > cb)
		                if(accessor(1) > cb)
		                  if(accessor(3) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) > cb)
		                      if(accessor(11) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(8) > cb)
		                    if(accessor(9) > cb)
		                      if(accessor(10) > cb)
		                        if(accessor(11) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(6) > cb)
		                  if(accessor(7) > cb)
		                    if(accessor(8) > cb)
		                      if(accessor(9) > cb)
		                        if(accessor(10) > cb)
		                          if(accessor(11) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(accessor(12) < c_b)
		          if(accessor(7) < c_b)
		            if(accessor(8) < c_b)
		              if(accessor(9) < c_b)
		                if(accessor(10) < c_b)
		                  if(accessor(11) < c_b)
		                    if(accessor(13) < c_b)
		                      if(accessor(6) < c_b)
		                        goto is_a_corner;
		                      else
		                        if(accessor(14) < c_b)
		                          if(accessor(15) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        if(accessor(12) > cb)
		          if(accessor(13) > cb)
		            if(accessor(14) > cb)
		              if(accessor(15) > cb)
		                if(accessor(1) > cb)
		                  if(accessor(3) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) > cb)
		                      if(accessor(11) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(8) > cb)
		                    if(accessor(9) > cb)
		                      if(accessor(10) > cb)
		                        if(accessor(11) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(6) > cb)
		                  if(accessor(7) > cb)
		                    if(accessor(8) > cb)
		                      if(accessor(9) > cb)
		                        if(accessor(10) > cb)
		                          if(accessor(11) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(accessor(12) < c_b)
		          if(accessor(7) < c_b)
		            if(accessor(8) < c_b)
		              if(accessor(9) < c_b)
		                if(accessor(10) < c_b)
		                  if(accessor(11) < c_b)
		                    if(accessor(13) < c_b)
		                      if(accessor(14) < c_b)
		                        if(accessor(6) < c_b)
		                          goto is_a_corner;
		                        else
		                          if(accessor(15) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		    else if(accessor(4) < c_b)
		      if(accessor(11) > cb)
		        if(accessor(12) > cb)
		          if(accessor(13) > cb)
		            if(accessor(10) > cb)
		              if(accessor(14) > cb)
		                if(accessor(15) > cb)
		                  if(accessor(1) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(8) > cb)
		                      if(accessor(9) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(6) > cb)
		                    if(accessor(7) > cb)
		                      if(accessor(8) > cb)
		                        if(accessor(9) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(5) > cb)
		                  if(accessor(6) > cb)
		                    if(accessor(7) > cb)
		                      if(accessor(8) > cb)
		                        if(accessor(9) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(1) > cb)
		                if(accessor(3) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(accessor(11) < c_b)
		        if(accessor(7) < c_b)
		          if(accessor(8) < c_b)
		            if(accessor(9) < c_b)
		              if(accessor(10) < c_b)
		                if(accessor(6) < c_b)
		                  if(accessor(5) < c_b)
		                    if(accessor(3) < c_b)
		                      goto is_a_corner;
		                    else
		                      if(accessor(12) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(12) < c_b)
		                      if(accessor(13) < c_b)
		                        if(accessor(14) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(12) < c_b)
		                    if(accessor(13) < c_b)
		                      if(accessor(14) < c_b)
		                        if(accessor(15) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      if(accessor(11) > cb)
		        if(accessor(12) > cb)
		          if(accessor(13) > cb)
		            if(accessor(10) > cb)
		              if(accessor(14) > cb)
		                if(accessor(15) > cb)
		                  if(accessor(1) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(8) > cb)
		                      if(accessor(9) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(6) > cb)
		                    if(accessor(7) > cb)
		                      if(accessor(8) > cb)
		                        if(accessor(9) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(5) > cb)
		                  if(accessor(6) > cb)
		                    if(accessor(7) > cb)
		                      if(accessor(8) > cb)
		                        if(accessor(9) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(1) > cb)
		                if(accessor(3) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(accessor(11) < c_b)
		        if(accessor(7) < c_b)
		          if(accessor(8) < c_b)
		            if(accessor(9) < c_b)
		              if(accessor(10) < c_b)
		                if(accessor(12) < c_b)
		                  if(accessor(13) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(5) < c_b)
		                        goto is_a_corner;
		                      else
		                        if(accessor(14) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(accessor(14) < c_b)
		                        if(accessor(15) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		  else if(accessor(2) < c_b)
		    if(accessor(9) > cb)
		      if(accessor(10) > cb)
		        if(accessor(11) > cb)
		          if(accessor(8) > cb)
		            if(accessor(12) > cb)
		              if(accessor(13) > cb)
		                if(accessor(14) > cb)
		                  if(accessor(15) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(4) > cb)
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(3) > cb)
		                if(accessor(4) > cb)
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(1) > cb)
		              if(accessor(12) > cb)
		                if(accessor(13) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(accessor(9) < c_b)
		      if(accessor(7) < c_b)
		        if(accessor(8) < c_b)
		          if(accessor(6) < c_b)
		            if(accessor(5) < c_b)
		              if(accessor(4) < c_b)
		                if(accessor(3) < c_b)
		                  if(accessor(1) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) < c_b)
		                    if(accessor(11) < c_b)
		                      if(accessor(12) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(10) < c_b)
		                  if(accessor(11) < c_b)
		                    if(accessor(12) < c_b)
		                      if(accessor(13) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(10) < c_b)
		                if(accessor(11) < c_b)
		                  if(accessor(12) < c_b)
		                    if(accessor(13) < c_b)
		                      if(accessor(14) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) < c_b)
		              if(accessor(11) < c_b)
		                if(accessor(12) < c_b)
		                  if(accessor(13) < c_b)
		                    if(accessor(14) < c_b)
		                      if(accessor(15) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else
		    if(accessor(9) > cb)
		      if(accessor(10) > cb)
		        if(accessor(11) > cb)
		          if(accessor(8) > cb)
		            if(accessor(12) > cb)
		              if(accessor(13) > cb)
		                if(accessor(14) > cb)
		                  if(accessor(15) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(4) > cb)
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(3) > cb)
		                if(accessor(4) > cb)
		                  if(accessor(5) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(7) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(1) > cb)
		              if(accessor(12) > cb)
		                if(accessor(13) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(accessor(9) < c_b)
		      if(accessor(7) < c_b)
		        if(accessor(8) < c_b)
		          if(accessor(10) < c_b)
		            if(accessor(11) < c_b)
		              if(accessor(6) < c_b)
		                if(accessor(5) < c_b)
		                  if(accessor(4) < c_b)
		                    if(accessor(3) < c_b)
		                      goto is_a_corner;
		                    else
		                      if(accessor(12) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(12) < c_b)
		                      if(accessor(13) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(12) < c_b)
		                    if(accessor(13) < c_b)
		                      if(accessor(14) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(12) < c_b)
		                  if(accessor(13) < c_b)
		                    if(accessor(14) < c_b)
		                      if(accessor(15) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		else if(accessor(0) < c_b)
		  if(accessor(2) > cb)
		    if(accessor(9) > cb)
		      if(accessor(7) > cb)
		        if(accessor(8) > cb)
		          if(accessor(6) > cb)
		            if(accessor(5) > cb)
		              if(accessor(4) > cb)
		                if(accessor(3) > cb)
		                  if(accessor(1) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) > cb)
		                    if(accessor(11) > cb)
		                      if(accessor(12) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(10) > cb)
		                  if(accessor(11) > cb)
		                    if(accessor(12) > cb)
		                      if(accessor(13) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(10) > cb)
		                if(accessor(11) > cb)
		                  if(accessor(12) > cb)
		                    if(accessor(13) > cb)
		                      if(accessor(14) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) > cb)
		              if(accessor(11) > cb)
		                if(accessor(12) > cb)
		                  if(accessor(13) > cb)
		                    if(accessor(14) > cb)
		                      if(accessor(15) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(accessor(9) < c_b)
		      if(accessor(10) < c_b)
		        if(accessor(11) < c_b)
		          if(accessor(8) < c_b)
		            if(accessor(12) < c_b)
		              if(accessor(13) < c_b)
		                if(accessor(14) < c_b)
		                  if(accessor(15) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(4) < c_b)
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(3) < c_b)
		                if(accessor(4) < c_b)
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(1) < c_b)
		              if(accessor(12) < c_b)
		                if(accessor(13) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else if(accessor(2) < c_b)
		    if(accessor(4) > cb)
		      if(accessor(11) > cb)
		        if(accessor(7) > cb)
		          if(accessor(8) > cb)
		            if(accessor(9) > cb)
		              if(accessor(10) > cb)
		                if(accessor(6) > cb)
		                  if(accessor(5) > cb)
		                    if(accessor(3) > cb)
		                      goto is_a_corner;
		                    else
		                      if(accessor(12) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(12) > cb)
		                      if(accessor(13) > cb)
		                        if(accessor(14) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(12) > cb)
		                    if(accessor(13) > cb)
		                      if(accessor(14) > cb)
		                        if(accessor(15) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(accessor(11) < c_b)
		        if(accessor(12) < c_b)
		          if(accessor(13) < c_b)
		            if(accessor(10) < c_b)
		              if(accessor(14) < c_b)
		                if(accessor(15) < c_b)
		                  if(accessor(1) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(8) < c_b)
		                      if(accessor(9) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(6) < c_b)
		                    if(accessor(7) < c_b)
		                      if(accessor(8) < c_b)
		                        if(accessor(9) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(5) < c_b)
		                  if(accessor(6) < c_b)
		                    if(accessor(7) < c_b)
		                      if(accessor(8) < c_b)
		                        if(accessor(9) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(1) < c_b)
		                if(accessor(3) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(accessor(4) < c_b)
		      if(accessor(5) > cb)
		        if(accessor(12) > cb)
		          if(accessor(7) > cb)
		            if(accessor(8) > cb)
		              if(accessor(9) > cb)
		                if(accessor(10) > cb)
		                  if(accessor(11) > cb)
		                    if(accessor(13) > cb)
		                      if(accessor(6) > cb)
		                        goto is_a_corner;
		                      else
		                        if(accessor(14) > cb)
		                          if(accessor(15) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(accessor(12) < c_b)
		          if(accessor(13) < c_b)
		            if(accessor(14) < c_b)
		              if(accessor(15) < c_b)
		                if(accessor(1) < c_b)
		                  if(accessor(3) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) < c_b)
		                      if(accessor(11) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(8) < c_b)
		                    if(accessor(9) < c_b)
		                      if(accessor(10) < c_b)
		                        if(accessor(11) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(6) < c_b)
		                  if(accessor(7) < c_b)
		                    if(accessor(8) < c_b)
		                      if(accessor(9) < c_b)
		                        if(accessor(10) < c_b)
		                          if(accessor(11) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(accessor(5) < c_b)
		        if(accessor(7) > cb)
		          if(accessor(14) > cb)
		            if(accessor(8) > cb)
		              if(accessor(9) > cb)
		                if(accessor(10) > cb)
		                  if(accessor(11) > cb)
		                    if(accessor(12) > cb)
		                      if(accessor(13) > cb)
		                        if(accessor(6) > cb)
		                          goto is_a_corner;
		                        else
		                          if(accessor(15) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else if(accessor(14) < c_b)
		            if(accessor(15) < c_b)
		              if(accessor(1) < c_b)
		                if(accessor(3) < c_b)
		                  if(accessor(6) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(13) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) < c_b)
		                    if(accessor(11) < c_b)
		                      if(accessor(12) < c_b)
		                        if(accessor(13) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(8) < c_b)
		                  if(accessor(9) < c_b)
		                    if(accessor(10) < c_b)
		                      if(accessor(11) < c_b)
		                        if(accessor(12) < c_b)
		                          if(accessor(13) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(accessor(7) < c_b)
		          if(accessor(3) < c_b)
		            if(accessor(1) < c_b)
		              if(accessor(6) < c_b)
		                if(accessor(8) < c_b)
		                  goto is_a_corner;
		                else
		                  if(accessor(15) < c_b)
		                    goto is_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(13) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(8) < c_b)
		                if(accessor(9) < c_b)
		                  if(accessor(10) < c_b)
		                    if(accessor(6) < c_b)
		                      goto is_a_corner;
		                    else
		                      if(accessor(11) < c_b)
		                        if(accessor(12) < c_b)
		                          if(accessor(13) < c_b)
		                            if(accessor(14) < c_b)
		                              if(accessor(15) < c_b)
		                                goto is_a_corner;
		                              else
		                                goto is_not_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) < c_b)
		              if(accessor(11) < c_b)
		                if(accessor(12) < c_b)
		                  if(accessor(8) < c_b)
		                    if(accessor(9) < c_b)
		                      if(accessor(6) < c_b)
		                        goto is_a_corner;
		                      else
		                        if(accessor(13) < c_b)
		                          if(accessor(14) < c_b)
		                            if(accessor(15) < c_b)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(accessor(1) < c_b)
		                        if(accessor(13) < c_b)
		                          if(accessor(14) < c_b)
		                            if(accessor(15) < c_b)
		                              goto is_a_corner;
		                            else
		                              goto is_not_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(1) < c_b)
		                      if(accessor(13) < c_b)
		                        if(accessor(14) < c_b)
		                          if(accessor(15) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(accessor(14) < c_b)
		            if(accessor(15) < c_b)
		              if(accessor(1) < c_b)
		                if(accessor(3) < c_b)
		                  if(accessor(6) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(13) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) < c_b)
		                    if(accessor(11) < c_b)
		                      if(accessor(12) < c_b)
		                        if(accessor(13) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(8) < c_b)
		                  if(accessor(9) < c_b)
		                    if(accessor(10) < c_b)
		                      if(accessor(11) < c_b)
		                        if(accessor(12) < c_b)
		                          if(accessor(13) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        if(accessor(12) > cb)
		          if(accessor(7) > cb)
		            if(accessor(8) > cb)
		              if(accessor(9) > cb)
		                if(accessor(10) > cb)
		                  if(accessor(11) > cb)
		                    if(accessor(13) > cb)
		                      if(accessor(14) > cb)
		                        if(accessor(6) > cb)
		                          goto is_a_corner;
		                        else
		                          if(accessor(15) > cb)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else if(accessor(12) < c_b)
		          if(accessor(13) < c_b)
		            if(accessor(14) < c_b)
		              if(accessor(15) < c_b)
		                if(accessor(1) < c_b)
		                  if(accessor(3) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) < c_b)
		                      if(accessor(11) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(8) < c_b)
		                    if(accessor(9) < c_b)
		                      if(accessor(10) < c_b)
		                        if(accessor(11) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(6) < c_b)
		                  if(accessor(7) < c_b)
		                    if(accessor(8) < c_b)
		                      if(accessor(9) < c_b)
		                        if(accessor(10) < c_b)
		                          if(accessor(11) < c_b)
		                            goto is_a_corner;
		                          else
		                            goto is_not_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		    else
		      if(accessor(11) > cb)
		        if(accessor(7) > cb)
		          if(accessor(8) > cb)
		            if(accessor(9) > cb)
		              if(accessor(10) > cb)
		                if(accessor(12) > cb)
		                  if(accessor(13) > cb)
		                    if(accessor(6) > cb)
		                      if(accessor(5) > cb)
		                        goto is_a_corner;
		                      else
		                        if(accessor(14) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                    else
		                      if(accessor(14) > cb)
		                        if(accessor(15) > cb)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else if(accessor(11) < c_b)
		        if(accessor(12) < c_b)
		          if(accessor(13) < c_b)
		            if(accessor(10) < c_b)
		              if(accessor(14) < c_b)
		                if(accessor(15) < c_b)
		                  if(accessor(1) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(8) < c_b)
		                      if(accessor(9) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(6) < c_b)
		                    if(accessor(7) < c_b)
		                      if(accessor(8) < c_b)
		                        if(accessor(9) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(5) < c_b)
		                  if(accessor(6) < c_b)
		                    if(accessor(7) < c_b)
		                      if(accessor(8) < c_b)
		                        if(accessor(9) < c_b)
		                          goto is_a_corner;
		                        else
		                          goto is_not_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(1) < c_b)
		                if(accessor(3) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		  else
		    if(accessor(9) > cb)
		      if(accessor(7) > cb)
		        if(accessor(8) > cb)
		          if(accessor(10) > cb)
		            if(accessor(11) > cb)
		              if(accessor(6) > cb)
		                if(accessor(5) > cb)
		                  if(accessor(4) > cb)
		                    if(accessor(3) > cb)
		                      goto is_a_corner;
		                    else
		                      if(accessor(12) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                  else
		                    if(accessor(12) > cb)
		                      if(accessor(13) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(12) > cb)
		                    if(accessor(13) > cb)
		                      if(accessor(14) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(12) > cb)
		                  if(accessor(13) > cb)
		                    if(accessor(14) > cb)
		                      if(accessor(15) > cb)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else if(accessor(9) < c_b)
		      if(accessor(10) < c_b)
		        if(accessor(11) < c_b)
		          if(accessor(8) < c_b)
		            if(accessor(12) < c_b)
		              if(accessor(13) < c_b)
		                if(accessor(14) < c_b)
		                  if(accessor(15) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(4) < c_b)
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(3) < c_b)
		                if(accessor(4) < c_b)
		                  if(accessor(5) < c_b)
		                    if(accessor(6) < c_b)
		                      if(accessor(7) < c_b)
		                        goto is_a_corner;
		                      else
		                        goto is_not_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(1) < c_b)
		              if(accessor(12) < c_b)
		                if(accessor(13) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		else
		  if(accessor(7) > cb)
		    if(accessor(8) > cb)
		      if(accessor(9) > cb)
		        if(accessor(6) > cb)
		          if(accessor(5) > cb)
		            if(accessor(4) > cb)
		              if(accessor(3) > cb)
		                if(accessor(2) > cb)
		                  if(accessor(1) > cb)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) > cb)
		                    if(accessor(11) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(10) > cb)
		                  if(accessor(11) > cb)
		                    if(accessor(12) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(10) > cb)
		                if(accessor(11) > cb)
		                  if(accessor(12) > cb)
		                    if(accessor(13) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) > cb)
		              if(accessor(11) > cb)
		                if(accessor(12) > cb)
		                  if(accessor(13) > cb)
		                    if(accessor(14) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(accessor(10) > cb)
		            if(accessor(11) > cb)
		              if(accessor(12) > cb)
		                if(accessor(13) > cb)
		                  if(accessor(14) > cb)
		                    if(accessor(15) > cb)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else if(accessor(7) < c_b)
		    if(accessor(8) < c_b)
		      if(accessor(9) < c_b)
		        if(accessor(6) < c_b)
		          if(accessor(5) < c_b)
		            if(accessor(4) < c_b)
		              if(accessor(3) < c_b)
		                if(accessor(2) < c_b)
		                  if(accessor(1) < c_b)
		                    goto is_a_corner;
		                  else
		                    if(accessor(10) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                else
		                  if(accessor(10) < c_b)
		                    if(accessor(11) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		              else
		                if(accessor(10) < c_b)
		                  if(accessor(11) < c_b)
		                    if(accessor(12) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		            else
		              if(accessor(10) < c_b)
		                if(accessor(11) < c_b)
		                  if(accessor(12) < c_b)
		                    if(accessor(13) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		          else
		            if(accessor(10) < c_b)
		              if(accessor(11) < c_b)
		                if(accessor(12) < c_b)
		                  if(accessor(13) < c_b)
		                    if(accessor(14) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		        else
		          if(accessor(10) < c_b)
		            if(accessor(11) < c_b)
		              if(accessor(12) < c_b)
		                if(accessor(13) < c_b)
		                  if(accessor(14) < c_b)
		                    if(accessor(15) < c_b)
		                      goto is_a_corner;
		                    else
		                      goto is_not_a_corner;
		                  else
		                    goto is_not_a_corner;
		                else
		                  goto is_not_a_corner;
		              else
		                goto is_not_a_corner;
		            else
		              goto is_not_a_corner;
		          else
		            goto is_not_a_corner;
		      else
		        goto is_not_a_corner;
		    else
		      goto is_not_a_corner;
		  else
		    goto is_not_a_corner;

		is_a_corner:
			bmin=b_test;
			goto end;

		is_not_a_corner:
			bmax=b_test;
			goto end;

		end:

		if(bmin == bmax - 1 || bmin == bmax)
			return bmin;
		b_test = (bmin + bmax) / 2;
	}
}

// pattern accessor:

const int Oast9_16_PatternAccessor::pattern_x[17]={0,-1,-2,-3,-3,-3,-2,-1,0,1,2,3,3,3,2,1,0};
const int Oast9_16_PatternAccessor::pattern_y[17]={-3,-3,-2,-1,0,1,2,3,3,3,2,1,0,-1,-2,-3,0};

unsigned char Oast9_16_PatternAccessor::operator()(unsigned int index){

	// get the position
	const float xf=x_c_+pattern_x[index]*scale_;
	const float yf=y_c_+pattern_y[index]*scale_;
	const cv::Mat& image=*img_;
	const int& imagecols=image.cols;

	// get the sigma_half:
	const float sigma_half=max(0.5,scale_/2.0);
	const float area=4.0*sigma_half*sigma_half;
	// calculate output:
	int ret_val;

	// this is the standard case (simple, not speed optimized yet):

	// scaling:
	const int scaling = 4194304.0/area;
	const int scaling2=float(scaling)*area/1024.0;

	// calculate borders
	const float x_1=xf-sigma_half;
	const float x1=xf+sigma_half;
	const float y_1=yf-sigma_half;
	const float y1=yf+sigma_half;

	const int x_left=int(x_1+0.5);
	const int y_top=int(y_1+0.5);
	const int x_right=int(x1+0.5);
	const int y_bottom=int(y1+0.5);

	// overlap area - multiplication factors:
	const float r_x_1=float(x_left)-x_1+0.5;
	const float r_y_1=float(y_top)-y_1+0.5;
	const float r_x1=x1-float(x_right)+0.5;
	const float r_y1=y1-float(y_bottom)+0.5;
	const int dx=x_right-x_left-1;
	const int dy=y_bottom-y_top-1;
	const int A=(r_x_1*r_y_1)*scaling;
	const int B=(r_x1*r_y_1)*scaling;
	const int C=(r_x1*r_y1)*scaling;
	const int D=(r_x_1*r_y1)*scaling;
	const int r_x_1_i=r_x_1*scaling;
	const int r_y_1_i=r_y_1*scaling;
	const int r_x1_i=r_x1*scaling;
	const int r_y1_i=r_y1*scaling;

	// now the calculation:
	uchar* ptr=image.data+x_left+imagecols*y_top;
	// first row:
	ret_val=A*int(*ptr);
	ptr++;
	const uchar* end1 = ptr+dx;
	for(; ptr<end1; ptr++){
		ret_val+=r_y_1_i*int(*ptr);
	}
	ret_val+=B*int(*ptr);
	// middle ones:
	ptr+=imagecols-dx-1;
	uchar* end_j=ptr+dy*imagecols;
	for(; ptr<end_j; ptr+=imagecols-dx-1){
		ret_val+=r_x_1_i*int(*ptr);
		ptr++;
		const uchar* end2 = ptr+dx;
		for(; ptr<end2; ptr++){
			ret_val+=int(*ptr)*scaling;
		}
		ret_val+=r_x1_i*int(*ptr);
	}
	// last row:
	ret_val+=D*int(*ptr);
	ptr++;
	const uchar* end3 = ptr+dx;
	for(; ptr<end3; ptr++){
		ret_val+=r_y1_i*int(*ptr);
	}
	ret_val+=C*int(*ptr);

	return 0xFF&((ret_val+scaling2/2)/scaling2/1024);
}
