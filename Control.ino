// The control.htm page ----------------------------------------------------------------------------------

const char html_control1[] = "<div class=\"t\"><table width=\"100%\"><tr><td><b>" Product " " Version " / %s %s";
const char html_control2[] = "</b></td><td align=\"right\"><b><font size=\"5\">CONTROL</font></b></td></tr></table><br />";
const char html_control3[] = "</div><div class=\"b\">\r\n";
const char html_control4a[] = 
"Date/Time:"
"<form method=\"get\" action=\"/control.htm\">"
"<button type=\"submit\" onclick=\"SetDateTime();\">Set</button> <span id=\"datetime\"></span>"
"<input id=\"dm\" type=\"hidden\" name=\"dm\">"
"<input id=\"dd\" type=\"hidden\" name=\"dd\">"
"<script>document.getElementById(\"datetime\").innerHTML = Date();</script>";
const char html_control4b[] = 
"<input id=\"dy\" type=\"hidden\" name=\"dy\">"
"<input id=\"th\" type=\"hidden\" name=\"th\">"
"<input id=\"tm\" type=\"hidden\" name=\"tm\">"
"<input id=\"ts\" type=\"hidden\" name=\"ts\">"
"</form><br />\r\n";
const char html_control4c[] =
"<script>\r\n"
"function SetDateTime() {"
"var d = new Date();"
"document.getElementById(\"dd\").value = d.getDate();"
"document.getElementById(\"dm\").value = d.getMonth();"
"document.getElementById(\"dy\").value = d.getFullYear();";
const char html_control4d[] =
"document.getElementById(\"th\").value = d.getHours();"
"document.getElementById(\"tm\").value = d.getMinutes();"
"document.getElementById(\"ts\").value = d.getSeconds();"
"}\r\n"
"</script>\r\n";
const char html_controlAlign1[] =
"Align: "
"<form method=\"get\" action=\"/control.htm\">"
"<button name=\"al\" value=\"1\" type=\"submit\">1 Star</button>";
const char html_controlAlign23[] = 
"<button name=\"al\" value=\"2\" type=\"submit\">2 Star</button>"
"<button name=\"al\" value=\"3\" type=\"submit\">3 Star</button>";
const char html_controlAlign4[] = 
"<br /><button name=\"al\" value=\"n\" type=\"submit\">Accept</button>"
"</form><br />\r\n";
const char html_control6[] = 
"Home/Park: "
"<form method=\"get\" action=\"/control.htm\">"
"<button name=\"hm\" value=\"r\" type=\"submit\">Home (Reset)</button>&nbsp;&nbsp;&nbsp;"
"<button name=\"hm\" value=\"f\" type=\"submit\">Find Home</button><br />";
const char html_control7[] = 
"<button name=\"pk\" value=\"p\" type=\"submit\">Park</button>&nbsp;&nbsp;&nbsp;"
"<button name=\"pk\" value=\"u\" type=\"submit\">Un-Park</button><br />"
"<button name=\"pk\" value=\"s\" type=\"submit\">Set-Park</button>"
"</form><br />\r\n";
const char html_control8[] = 
"Tracking: "
"<form method=\"get\" action=\"/control.htm\">"
"<button name=\"tk\" value=\"on\" type=\"submit\">On</button>"
"<button name=\"tk\" value=\"off\" type=\"submit\">Off</button>&nbsp;&nbsp;&nbsp;";
const char html_control9[] = 
"<button name=\"tk\" value=\"f\" type=\"submit\">+ (0.1Hz faster)</button>"
"<button name=\"tk\" value=\"-\" type=\"submit\">- (0.1Hz slower)</button>"
"<button name=\"tk\" value=\"r\" type=\"submit\">Reset (default)</button><br />";
const char html_control10[] = 
"<button name=\"tk\" value=\"s\" type=\"submit\">Sidereal</button>"
"<button name=\"tk\" value=\"l\" type=\"submit\">Lunar</button>"
"<button name=\"tk\" value=\"h\" type=\"submit\">Solar</button>";
const char html_control11[] = 
"</br></br>Compensated Tracking Rate (Pointing Model/Refraction): </br>"
"<button name=\"rr\" value=\"otk\" type=\"submit\">Full</button>"
"<button name=\"rr\" value=\"on\" type=\"submit\">Refraction Only</button>"
"<button name=\"rr\" value=\"off\" type=\"submit\">Off</button>";
const char html_control12[] = 
"</br></br>Auto-continue (automatic Meridian flip): </br>"
"<button name=\"ac\" value=\"on\" type=\"submit\">On</button>"
"<button name=\"ac\" value=\"off\" type=\"submit\">Off</button>";
const char html_control13[] = 
"</form>\r\n";

void handleControl() {
  Serial.setTimeout(WebTimeout);

  char temp[320] = "";
  char temp1[80]="";
  char temp2[80]="";
  char temp3[80]="";

  processControlGet();

  String data=html_head1;
  data += html_main_css1;
  data += html_main_css2;
  data += html_main_css3;
  data += html_main_css4;
  data += html_main_css5;
  data += html_main_css6;
  data += html_main_css7;
  data += html_main_css8;
  data += html_main_css9;
  data += html_head2;

  // get status
  char stat[20] = "";
  Serial.print(":GU#");
  stat[Serial.readBytesUntil('#',stat,20)]=0;

  // finish the standard http response header
  Serial.print(":GVP#");
  temp2[Serial.readBytesUntil('#',temp2,20)]=0; 
  if (strlen(temp2)<=0) { strcpy(temp2,"N/A"); }
  Serial.print(":GVN#");
  temp3[Serial.readBytesUntil('#',temp3,20)]=0; 
  if (strlen(temp3)<=0) { strcpy(temp3,"N/A"); }
  sprintf(temp,html_control1,temp2,temp3);
  data += temp;
  data += html_control2;
  data += html_links1;
  data += html_links2;
  data += html_links3;

  // and the remainder of the page
  data += html_control3;
  data += html_control4a;
  data += html_control4b;
  data += html_control4c;
  data += html_control4d;
  data += html_controlAlign1;
  if ((!strstr(stat,"A")) && (!strstr(stat,"k"))) {  // not AltAzm and not Fork_Alt
    data += html_controlAlign23;
  }
  data += html_controlAlign4;
  data += html_control6;
  data += html_control7;
  data += html_control8;
  data += html_control9;
  data += html_control10;
  if (!strstr(stat,"A")) {  // not AltAzm
    data += html_control11;
  }
  data += html_control12;
  if ((!strstr(stat,"A")) && (!strstr(stat,"k"))) {  // not AltAzm and not Fork_Alt
    data += html_control13;
  }
  data += "</div></body></html>";
  
  server.send(200, "text/html",data);
}

int get_temp_month;
int get_temp_day;
int get_temp_year;
int get_temp_hour;
int get_temp_minute;
int get_temp_second;

void processControlGet() {
  // from the Control.htm page -------------------------------------------------------------------
  String v;
  int i;
  char temp[20]="";

  // Date/Time
  v=server.arg("dm");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=0) && (i<=11))) { get_temp_month=i+1; }
  }
  v=server.arg("dd");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=1) && (i<=31))) { get_temp_day=i; }
  }
  v=server.arg("dy");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=2016) && (i<=9999))) {
      get_temp_year=i-2000;
      char temp[10];
      sprintf(temp,":ST%02d/%02d/%02d#",get_temp_month,get_temp_day,get_temp_year);
      Serial.print(temp);
    }
  }
  v=server.arg("th");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=0) && (i<=23))) { get_temp_hour=i; }
  }
  v=server.arg("tm");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=0) && (i<=59))) { get_temp_minute=i; }
  }
  v=server.arg("ts");
  if (v!="") {
    if ( (atoi2((char *)v.c_str(),&i)) && ((i>=0) && (i<=59))) {
      get_temp_second=i;
      char temp[10];
      sprintf(temp,":SL%02d:%02d:%02d#",get_temp_hour,get_temp_minute,get_temp_second);
      Serial.print(temp);
    }
  }
  // Align
  v=server.arg("al");
  if (v!="") {
    if (v=="1") Serial.print(":A1#");
    if (v=="2") Serial.print(":A2#");
    if (v=="3") Serial.print(":A3#");
    if (v=="n") Serial.print(":A+#");
  }
  // Home/Park
  v=server.arg("hm");
  if (v!="") {
    if (v=="r") Serial.print(":hF#");
    if (v=="f") Serial.print(":hC#");
  }
  v=server.arg("pk");
  if (v!="") {
    if (v=="p") Serial.print(":hP#");
    if (v=="u") Serial.print(":hR#");
    if (v=="s") Serial.print(":hQ#");
  }
  // Tracking control
  v=server.arg("tk");
  if (v!="") {
    if (v=="on") Serial.print(":Te#");
    if (v=="off") Serial.print(":Td#");
    if (v=="f") Serial.print(":T+#"); // 0.02hz faster
    if (v=="-") Serial.print(":T-#"); // 0.02hz slower
    if (v=="r") Serial.print(":TR#"); // reset
    if (v=="s") Serial.print(":TQ#"); // sidereal
    if (v=="l") Serial.print(":TL#"); // lunar
    if (v=="h") Serial.print(":TS#"); // solar
  }
  // Refraction Rate Tracking control
  v=server.arg("rr");
  if (v!="") {
    if (v=="otk") Serial.print(":To#");
    if (v=="on") Serial.print(":Tr#");
    if (v=="off") Serial.print(":Tn#");
  }
  // Auto-continue
  v=server.arg("ac");
  if (v!="") {
    if (v=="on") Serial.print(":SX95,1#");
    if (v=="off") Serial.print(":SX95,0#");
  }

  // clear any possible response
  temp[Serial.readBytesUntil('#',temp,20)]=0;
}

