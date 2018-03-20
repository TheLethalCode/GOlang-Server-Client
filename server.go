package main

import (
	"net/http"
	//"fmt"
	"io/ioutil"
	"io"
	"strings"
	"encoding/csv"
)


func extractemail(w http.ResponseWriter, r *http.Request) {
	
	io.WriteString(w,"\nRequest Recieved\n")

	dat, err := ioutil.ReadFile(r.URL.Path[1:])
	if err != nil {
		io.WriteString(w,"Unable to open file\n")
		return 
	}
	
	hi := csv.NewReader(strings.NewReader(string(dat)))
	record, err := hi.Read()
	var val int
	for i:=0;i<len(record);i=i+1 {
		if strings.Contains(record[i],"email") || strings.Contains(record[i],"Email") {
			val = i
			break
		}
	}
	if val==len(record) {
		io.WriteString(w,"No email field found\n")
		return
	}

	var flag int 
	for {
		record, err := hi.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			panic(err)
		}
		temp := 0
		for i:=0;i<len(record[val]);i++{
			if record[val][i] != ' ' {
				temp = 1
				break
			}
		}
		if temp==0 {
			continue
		}
		if !strings.Contains(record[val],"@") && temp == 1 {
			io.WriteString(w,"Invalid E-mail found" + "\n")
			continue
		} 
		flag = 1
		io.WriteString(w,"\n"+record[val]+"\n")
	}
	if flag == 0 {
		io.WriteString(w,"No emails found in the email field" + "\n")
	}
}

func main(){
	http.HandleFunc("/", extractemail)
	http.ListenAndServe(":8000", nil)
}