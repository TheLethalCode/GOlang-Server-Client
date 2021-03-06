package main

import (
	"net/http"
	"bytes"
	"io"
	"strings"
    "encoding/csv"
	"fmt"
	"strconv"
)


func extractemail(w http.ResponseWriter, r *http.Request) {
	
	var Buf bytes.Buffer
	file, _ , err := r.FormFile("file")
	if err != nil {
		io.WriteString(w,"Cannot open file\n")
		return
	}

	io.Copy(&Buf, file)
	
	hi := csv.NewReader(strings.NewReader(Buf.String()))
	record, err := hi.Read()
	if err != nil {
		io.WriteString(w,"Error processing the csv file\n")
		return
	}
	
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
		flag = flag + 1
		io.WriteString(w,"\n"+record[val]+"\n")
	}
	if flag == 0 {
		io.WriteString(w,"No emails found in the email field" + "\n")
		return
	} else {
	io.WriteString(w,strconv.Itoa(flag) + " emails sent")
	}
	fmt.Println(flag," emails processed")
	file.Close()
}

func main(){
	http.HandleFunc("/", extractemail)
	http.ListenAndServe(":8000", nil)
}
