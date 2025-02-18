 # Advanced C project:   
本專案是一個模擬 Linux 環境下的檔案系統，允許使用者透過 Command Line 進行檔案管理，例如建立、編輯、儲存與加密檔案。  
在使用系統前，使用者需選擇：  
1. 載入現有的 dump 檔案，以恢復先前的檔案系統狀態。  
2. 建立新的儲存空間，並輸入儲存空間大小（如 100MB），系統將據此建立對應的儲存空間，並根據需求動態分配與管理儲存空間。  
# 主要功能:  
  自訂命令列:  
  提供簡單直覺的指令，讓使用者可以管理檔案與目錄。  
  檔案系統:  
  建立與編輯文字檔案、儲存與讀取檔案、目錄與檔案管理（新增、刪除、變更名稱）  
  安全性機制:  
  透過密碼保護dump檔案，且使用加密技術加密dump檔案，並在載入dump檔案時自動解密   
# 基本操作如下:  
'ls' list directory  
'cd' change directory  
'rm' remove file  
'mkdir' make directory  
'rmdir' remove directory  
'put' put file into the space  
'get' get file from the space  
'create' create file into the space  
'edit' edit file content in the space  
'rename' rename file name in the space  
'cat' show content  
'status' show status of the space  
'help' print help information  
'exit and store img'  store dump file
# 示範影片:  
https://youtu.be/HsRZ85Nur8g?si=nA_Y80cAS1He3IIa

