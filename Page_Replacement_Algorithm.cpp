#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include<cmath>
#include <vector>
#include <queue>
using namespace std;

typedef struct save_Frame{
	int sTime, sBit, sCounter ;
	string sshift ,  sBit2 ;
	char sID ;
	bool sjj ;
} sFrame ;

string which_small(vector<sFrame> v3) {
	vector<sFrame> array = v3 ;
	for (int i = array.size() - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (array[j].sshift > array[j+1].sshift )
                swap(array[j], array[j + 1]);
    return array[0].sshift ;
}

int main() {
	cout << "Welcome To OS Project two !" << endl ;
	int c = -1,total = 0 , Page_Frame = -1, time_slice = -1,go_out = -1 ;
	string input = "",output = "", junk = "", Page_Reference = "" ;
	cout << "Please input file name (do not add .txt):";
	cin >> input ;
	output = input+"_output.txt" ;
	input += ".txt" ;
	fstream fin(input.c_str()), fin_out(output.c_str(), ios::out) ;
	vector<sFrame> v1 ;
	if(!fin){    cout << "File not found." << endl;   }
	else {
      fin >> Page_Frame >> Page_Reference;
	  
      for ( int i = 0 ; i < Page_Reference.size(); i++) {
      	sFrame add ;
      	add.sID = Page_Reference[i];
      	add.sBit = 1 ;
      	add.sBit2 = "0" ;
      	add.sCounter = 1 ;
      	add.sshift = "" ;
      	add.sjj = false ;
		v1.push_back(add) ;	
	  } // Ū�J�ɮסA�ó]�w��l�� 
	  
	  vector<sFrame> v2 ;
	  int Page_Fault_num = 0,  Page_Replaces = 0 ;
	  fin_out << "--------------FIFO-----------------------" << endl ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;  // �]�w�C����  Page_Fault �� false  
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v2.size() ; j++ ) {
	  	  if ( v2[j].sID == v1[i].sID ) Page_Fault = true ;
	    }  //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v2.size() < Page_Frame ) // �p�G��J���`�� �p��pageframe �N�����[�J 
	   		v2.push_back( v1[i] ) ;
		  else
		  	v2.erase(v2.begin()), v2.push_back( v1[i] ), Page_Replaces++ ; // �p�G��J���`�� �j��pageframe �N���R���Ĥ@��frame �b�[�J  
		  for ( int j = v2.size()-1 ; j >= 0 ; j-- ) fin_out << v2[j].sID ; //�L�X  
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
	      for ( int j = v2.size()-1 ; j >= 0 ; j-- ) fin_out << v2[j].sID ;  //�L�X 
		  fin_out << endl ;	
		}
	  }
	  
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;
	  
	  
	  fin_out << "--------------LRU--------------------------" << endl ;
	  vector<sFrame> v3 ;
	  Page_Fault_num = 0,  Page_Replaces = 0 ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	  if ( v3[j].sID == v1[i].sID ) {
			Page_Fault = true,v3.erase(v3.begin()+j); // ���@�˴N��L���}�C�̫᭱�A�۷�󵹥L�@�ӷs���ɶ��W�O 
			break ;
		  }
	    } //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v3.size() < Page_Frame )
	   		v3.push_back( v1[i] ) ; // �p�G��J���`�� �p��pageframe �N�����[�J  
		  else
		  	v3.erase(v3.begin()), v3.push_back( v1[i] ), Page_Replaces++ ;   // �p�G��J���`�� �j��pageframe �N���R���Ĥ@��frame �b�[�J 
		  for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;   
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
	      v3.push_back( v1[i] ) ;	
	      for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  fin_out << endl ;	
		}
	  }
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;
	  
	  fin_out << "--------------Additional Reference Bits-------------------" << endl ;
	  v3.clear() ;
	  vector<sFrame> v4 = v1 ;
	  Page_Fault_num = 0,  Page_Replaces = 0 ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;
	  	sFrame qqq ;
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	  if ( v3[j].sID == v4[i].sID ) {
			Page_Fault = true,v3[j].sBit2 = "1",v3[j].sTime = i, qqq = v3[j], v3.erase(v3.begin()+j) ;
			break ;
		  }
	    } //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v3.size() < Page_Frame )
	   		v4[i].sTime = i,v4[i].sBit2 = "1", v3.push_back( v4[i] ) ;
		  else {
		  	bool go_out = false ;
		  	string k = which_small(v3) ; // ��}�C���ݽ֪�shift�̤p 
		  	for ( int g = 0 ; g < v3.size() ; g++ ) { //��Xshift�̤p�A�ɶ��S�̦��� 
		  	  if (v3[g].sshift == k ) {
		  	    v4[i].sshift = v3[g].sshift, v3.erase(v3.begin()+g),v4[i].sBit2 = "1",v4[i].sTime = i, v3.push_back( v4[i] ) ;
		  	    go_out = true; 
			    break ;
		      }
		    }
		  	Page_Replaces++;
		  }
		   
		  for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
		  v3.push_back( qqq ) ;	
	      for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  fin_out << endl ;	
		}
		
		for ( int g = 0 ; g < v3.size() ; g++ ) {
          v3[g].sshift = v3[g].sBit2 + v3[g].sshift ;
          v3[g].sBit2 = "0" ;
		}
	  }
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;

	  fin_out << "--------------Second chance Page-------------------------" << endl ;
	  v3.clear() ;
	  Page_Fault_num = 0,  Page_Replaces = 0 ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;
	  	sFrame qqqq ;
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	  if ( v3[j].sID == v1[i].sID ) {
			Page_Fault = true ;
			//if ( v3[j].sjj == false ) v3[j].sBit = 1, v3[j].sjj = true  ;
			break ;
		  }
	    } //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v3.size() < Page_Frame )
	   		v3.push_back( v1[i] ) ;
		  else {
		  	while (true) {
		  	  if (v3[0].sBit == 1 ) { // �p�Gbit�� 1 �h�A���L�@�����|�A��L���}�C�̫᭱�A�۷�󵹥L�s���ɶ��W�O 
		  	    v3[0].sBit = 0 ;	
 		        sFrame sss = v3[0]; 
		  	    v3.erase(v3.begin()), v3.push_back( sss ) ;
		      }
		      else { // �p�Gbit�� 0�A�h�����R�� 
		      	v3.erase(v3.begin()), v3.push_back( v1[i] ) ;
		      	break;
			  }
		    }
		  	Page_Replaces++;
		  }
		   
		  for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
		  for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	    if ( v3[j].sID == v1[i].sID ) {
			  if ( v3[j].sjj == false ) v3[j].sBit = 1, v3[j].sjj = true  ;
			  break ;
		    }
		    else v3[j].sBit = 0 ;
	      }
			
	      for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  fin_out << endl ;	
		}
	  }
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;
	  
	  
	  fin_out << "--------------Least Frequently Used Page Replacement --------------------" << endl ;
	  v3.clear() ;
	  v4.clear() ;
	  v4 = v1 ;
	  Page_Fault_num = 0,  Page_Replaces = 0 ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;
	  	sFrame qqq ;
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	  if ( v3[j].sID == v4[i].sID ) {
			Page_Fault = true,v3[j].sCounter++,v3[j].sTime = i ; // , qqq = v3[j], v3.erase(v3.begin()+j) ;
			break ;
		  }
	    } //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v3.size() < Page_Frame )
	   		v4[i].sTime = i,  v3.push_back( v4[i] ) ;
		  else {
		  	bool go_out = false ;
		  	for (int h = 1 ; go_out == false ; h++ ) {
		  	  for ( int g = 0 ; g < v3.size() ; g++ ) {
		  	    if (v3[g].sCounter == h ) {
		  	      v3.erase(v3.begin()+g),v4[i].sTime = i, v3.push_back( v4[i] ) ;
		  	      go_out = true; 
				  break ;
		        }
		      }
		    }
		  	Page_Replaces++;
		  }
		   
		  for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
		  //v3.push_back( qqq ) ;	
	      for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  fin_out << endl ;	
		}
	  }
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;
	  
	  
	  fin_out << "--------------Most Frequently Used Page Replacement ------------------------" << endl ;
	  v3.clear() ;
	  v4.clear() ;
	  v4 = v1 ;
	  Page_Fault_num = 0,  Page_Replaces = 0 ;
	  for ( int i = 0 ; i < v1.size() ; i++ ) {
	  	bool Page_Fault = false ;
	  	sFrame qqq ;
	  	fin_out << v1[i].sID << "\t" ;
	  	for ( int j = 0 ; j < v3.size() ; j++ ) {
	  	  if ( v3[j].sID == v4[i].sID ) {
			Page_Fault = true,v3[j].sCounter++,v3[j].sTime = i, qqq = v3[j], v3.erase(v3.begin()+j) ;
			break ;
		  }
	    } //�p�G���@�˪� �N�]�w��true�A�N�N��S��page_fault 
	  	  
	 	if ( Page_Fault == false ) {
	   	  if ( v3.size() < Page_Frame )
	   		v4[i].sTime = i,  v3.push_back( v4[i] ) ;
		  else {
		  	bool go_out = false ;
		  	for (int h = 100 ; go_out == false ; h-- ) {
		  	  for ( int g = v3.size() - 1 ; g >= 0 ; g-- ) {
		  	    if (v3[g].sCounter == h ) {
		  	      v3.erase(v3.begin()+g),v4[i].sTime = i, v3.push_back( v4[i] ) ;
		  	      go_out = true; 
				  break ;
		        }
		      }
		    }
		  	Page_Replaces++;
		  }
		   
		  for ( int j = 0 ; j < v3.size() ; j++ ) fin_out << v3[j].sID ;
		  Page_Fault_num++;
		  fin_out << "\t" << "F"  << endl ;
	    }
	    else {
		  v3.push_back( qqq ) ;	
	      for ( int j = v3.size()-1 ; j >= 0 ; j-- ) fin_out << v3[j].sID ;
		  fin_out << endl ;	
		}
	  }
	  fin_out << "Page Fault = " << Page_Fault_num << "  Page Replaces = " << Page_Replaces << "  Page Frames = " <<Page_Frame << endl << endl ;
	}
    
    fin_out.close() ;
    fin.close();
	return 0 ;
}

