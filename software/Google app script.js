function doGet(e)
 { 
  Logger.log( JSON.stringify(e) ); 
  var result = 'Ok'; 
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '12RBrIHB2Uu7keczcRc2hVpjb8Zx_xeakiNXVJTjVXd4'; 		
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();	
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    d=new Date();
    rowData[0] = d; 
    rowData[1] = d.toLocaleTimeString(); 
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'PH Sensor Values': 
          rowData[2] = value;
            if(rowData[2]<7)
           {
              rowData[3]="Acid";
           }
           else if(rowData[2]===7)
           {
             rowData[3]="Neutral";

           }
           else
           {
             rowData[3]="Alkaline";
           }
         
          break;
        case 'Turbidity Sensor values': 
          rowData[4] = value; 
          if(rowData[4]<20)
           {
              rowData[5]="Clear";
           }
           else if(rowData[4]>20 && rowData[4]<50)
           {
             rowData[5]="Cloudy";

           }
           else
           {
             rowData[5]="Dirty";
           }
          break;
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
 
  return ContentService.createTextOutput(result);
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
