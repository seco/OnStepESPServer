// The guide.htm page

const char html_guide1[] = "<div class=\"t\"><table width=\"100%\"><tr><td><b><font size=\"5\">%s</font></b></td><td align=\"right\"><b>" Product " " Version " (OnStep %s)</b>";
const char html_guide2[] = "</td></tr></table>";
//const char html_guide1[] = "<div class=\"t\"><table width=\"100%\"><tr><td><b>" Product " " Version " / %s %s";
//const char html_guide2[] = "</b></td><td align=\"right\"><b><font size=\"5\">GUIDE</font></b></td></tr></table><br />";
const char html_guide3[] = "</div><div class=\"b\">\r\n";
const char html_guide4[] = 
"<script>function guide(dir,start) { var xhttp = new XMLHttpRequest(); "
"xhttp.open('GET', 'guide.txt?dr='+dir+start+'&x='+new Date().getTime(), true);"
"xhttp.send(); }</script>"
"Guide Rate:<br />";
const char html_guideControls1[] =
"<form method=\"get\" action=\"/guide.htm\">"
"<button name=\"gu\" value=\"1\" type=\"submit\">0.5x</button>";
const char html_guideControls2[] = 
"<button name=\"gu\" value=\"2\" type=\"submit\">1x</button>"
"<button name=\"gu\" value=\"4\" type=\"submit\">Mid</button>";
const char html_guideControls3[] = 
"<button name=\"gu\" value=\"6\" type=\"submit\">Fast</button>"
"<button name=\"gu\" value=\"8\" type=\"submit\">VFast</button></form><br />Guide:<br />";
const char html_guideControls4[] =
"<div style=\"float: left; border: 2px solid #551111; background-color: #181818; text-align: center; padding: 15px; margin: 5px;\">"
"<button type=\"button\" style=\"width: 60px; height: 50px;\" onmousedown=\"guide('n','1')\" onmouseup=\"guide('n','0')\">North</button><br />";
const char html_guideControls5[] = 
"<button type=\"button\" style=\"width: 60px; height: 50px;\" onmousedown=\"guide('e','1')\" onmouseup=\"guide('e','0')\">East</button>";
const char html_guideControls6[] = 
"<button type=\"button\" style=\"width: 60px; height: 50px;\" onclick=\"guide('s','y')\">Sync</button>"
"<button type=\"button\" style=\"width: 60px; height: 50px;\" onmousedown=\"guide('w','1')\" onmouseup=\"guide('w','0')\">West</button><br />";
const char html_guideControls7[] = 
"<button type=\"button\" style=\"width: 60px; height: 50px;\" onmousedown=\"guide('s','1')\" onmouseup=\"guide('s','0')\">South</button>"
"</div><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />";
const char html_guideControls8[] = 
"<form method=\"get\" action=\"/guide.htm\">"
">&nbsp;<button name=\"gu\" value=\"q\" type=\"submit\" style=\"height: 40px;\">Stop Slew/Guide!</button>&nbsp;<<br /><br /></form>\r\n";

void handleGuide() {
  Serial.setTimeout(WebTimeout);
    
  char temp[320] = "";
  char temp1[80]="";
  char temp2[80]="";
  char temp3[80]="";

  processGuideGet();
  
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

  // finish the standard http response header
  Serial.print(":GVP#");
  temp2[Serial.readBytesUntil('#',temp2,20)]=0; 
  if (strlen(temp2)<=0) { strcpy(temp2,"N/A"); } else { for (int i=2; i<7; i++) temp2[i]=temp2[i+1]; }
  Serial.print(":GVN#");
  temp3[Serial.readBytesUntil('#',temp3,20)]=0;
  if (strlen(temp3)<=0) { strcpy(temp3,"N/A"); }
  sprintf(temp,html_guide1,temp2,temp3);
  data += temp;
  data += html_guide2;
  data += html_links1gu;
  data += html_links2gu;
  data += html_links3gu;

  data += html_guide3;
  data += html_guide4;

  data += html_guideControls1;
  data += html_guideControls2;
  data += html_guideControls3;
  data += html_guideControls4;
  data += html_guideControls5;
  data += html_guideControls6;
  data += html_guideControls7;
  data += html_guideControls8;
  data += "</div></body></html>";

  server.send(200, "text/html",data);
}

void handleGuideAjax() {
  processGuideGet();
  server.send(200, "text/html","");
}

void processGuideGet() {
  String v;
  int i;
  char temp[20]="";

  // GUIDE control -----------------------------------------------
  v=server.arg("gu");
  if (v!="") {
    if (v=="0") Serial.print(":R0#");
    if (v=="1") Serial.print(":R1#");
    if (v=="2") Serial.print(":R2#");
    if (v=="3") Serial.print(":R3#");
    if (v=="4") Serial.print(":R4#");
    if (v=="5") Serial.print(":R5#");
    if (v=="6") Serial.print(":R6#");
    if (v=="7") Serial.print(":R7#");
    if (v=="8") Serial.print(":R8#");
    if (v=="9") Serial.print(":R9#");
    if (v=="q") Serial.print(":Q#");
  }
  v=server.arg("dr");
  if (v!="") {
    if (v=="n1") Serial.print(":Mn#");
    if (v=="s1") Serial.print(":Ms#");
    if (v=="e1") Serial.print(":Me#");
    if (v=="w1") Serial.print(":Mw#");

    if (v=="n0") Serial.print(":Qn#");
    if (v=="s0") Serial.print(":Qs#");
    if (v=="e0") Serial.print(":Qe#");
    if (v=="w0") Serial.print(":Qw#");
  }
}


