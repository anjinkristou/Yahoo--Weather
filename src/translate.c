#include "translate.h"
  

bool TranslateDate(char language, char *month_text, char *weekday_text)
{
    bool translate_sp = false;
    
    switch(language){
    case 'E': //SPANISH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   enero", strlen("   enero")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   febrero", strlen("   febrero")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   marzo", strlen("   marzo")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   abril", strlen("   abril")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   mayo", strlen("   mayo")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   junio", strlen("   junio")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   julio", strlen("   julio")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   agosto", strlen("   agosto")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   septiembre", strlen("   septiembre")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   octubre", strlen("   octubre")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   noviembre", strlen("   noviembre")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   diciembre", strlen("   diciembre")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Lunes", strlen("Lunes")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Martes", strlen("Martes")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Miércoles", strlen("Miércoles")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Jueves", strlen("Jueves")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Viernes", strlen("Viernes")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Sábado", strlen("Sábado")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Domingo", strlen("Domingo")+1); // Sunday
        }
        
    }//END OF SPANISH
        break;
    case 'I': //ITALIAN
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   gennaio", strlen("   gennaio")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   febbraio", strlen("   febbraio")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   marzo", strlen("   marzo")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   aprile", strlen("   aprile")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   maggio", strlen("   maggio")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   giugno", strlen("   giugno")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   luglio", strlen("   luglio")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   agosto", strlen("   agosto")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   settembre", strlen("   settembre")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   ottobre", strlen("   ottobre")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   novembre", strlen("   novembre")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   dicembre", strlen("   dicembre")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Lunedi", strlen("Lunedi")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Martedi", strlen("Martedi")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Mercoledi", strlen("Mercoledi")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Giovedi", strlen("Giovedi")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Venerdi", strlen("Venerdi")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Sabato", strlen("Sabato")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Domenica", strlen("Domenica")+1); // Sunday
        }
        
    } //END OF ITALIAN
        break;
    case 'G': //GERMAN
    {
        translate_sp= true;
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "  .Januar", strlen("  .Januar")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "  .Februar", strlen("  .Februar")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "  .März", strlen("  .März")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "  .April", strlen("  .April")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "  .Mai", strlen("  .Mai")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "  .Juni", strlen("  .Juni")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "  .Juli", strlen("  .Juli")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "  .August", strlen("  .August")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "  .September", strlen("  .September")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "  .Oktober", strlen("  .Oktober")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "  .November", strlen("  .November")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "  .Dezember", strlen("  .Dezember")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Montag", strlen("Montag")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Dienstag", strlen("Dienstag")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Mittwoch", strlen("Mittwoch")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Donnerstag", strlen("Donnerstag")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Freitag", strlen("Freitag")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Samstag", strlen("Samstag")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Sonntag", strlen("Sonntag")+1); // Sunday
        }
        
    } //END OF GERMAN
        break;
    case 'C': //CZECH
    {
        translate_sp= true;
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "Leden ", strlen("Leden ")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "Únor ", strlen("Únor ")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "Brezen ", strlen("Brezen ")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "Duben ", strlen("Duben ")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "Květen ", strlen("Květen ")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "Červen ", strlen("Červen ")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "Červenec ", strlen("Červenec ")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "Srpen ", strlen("Srpen ")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "Zárí ", strlen("Zárí ")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "Ríjen ", strlen("Ríjen ")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "Listopad ", strlen("Listopad ")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "Prosinec ", strlen("Prosinec ")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Pondělí", strlen("Pondělí")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Úterý", strlen("Úterý")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Streda", strlen("Streda")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Čtvrtek", strlen("Čtvrtek")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Pátek", strlen("Pátek")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Sobota", strlen("Sobota")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Neděle", strlen("Neděle")+1); // Sunday
        }
        
    } //END OF CZECH
        break;
    case 'F': //FRENCH
    {
        translate_sp= true;
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   janvier", strlen("   janvier")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   février", strlen("   février")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   mars", strlen("   mars")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   avril", strlen("   avril")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   mai", strlen("   mai")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   juin", strlen("   juin")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   juillet", strlen("   juillet")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   août", strlen("   août")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   septembre", strlen("   septembre")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   octobre", strlen("   octobre")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   novembre", strlen("   novembre")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   décembre", strlen("   décembre")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Lundi", strlen("Lundi")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Mardi", strlen("Mardi")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Mercredi", strlen("Mercredi")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Jeudi", strlen("Jeudi")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Vendredi", strlen("Vendredi")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Samedi", strlen("Samedi")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Dimanche", strlen("Dimanche")+1); // Sunday
        }
        
    } //END OF FRENCH
        break;
    case 'P': //PORTUGUESE
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   Janeiro", strlen("   Janeiro")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Fevereiro", strlen("   Fevereiro")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   Março", strlen("   Março")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   Abril", strlen("   Abril")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   Maio", strlen("   Maio")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   Junho", strlen("   Junho")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   Julho", strlen("   Julho")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   Agosto", strlen("   Agosto")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Setembro", strlen("   Setembro")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   Outubro", strlen("   Outubro")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   Novembro", strlen("   Novembro")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Dezembro", strlen("   Dezembro")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Segunda", strlen("Segunda")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Terça", strlen("Terça")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Quarta", strlen("Quarta")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Quinta", strlen("Quinta")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Sexta", strlen("Sexta")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Sábado", strlen("Sábado")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Domingo", strlen("Domingo")+1); // Sunday
        }
        
    } //END OF PORTUGUESE
        break;
    case 'X': //FINNISH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "  . Tammikuu", strlen("  . Tammikuu")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "  . Helmikuu", strlen("  . Helmikuu")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "  . Maaliskuu", strlen("  . Maaliskuu")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "  . Huhtikuu", strlen("  . Huhtikuu")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "  . Toukokuu", strlen("  . Toukokuu")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "  . Kesäkuu", strlen("  . Kesäkuu")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "  . Heinäkuu", strlen("  . Heinäkuu")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "  . Elokuu", strlen("  . Elokuu")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "  . Syyskuu", strlen("  . Syyskuu")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "  . Lokakuu", strlen("  . Lokakuu")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "  . Marraskuu", strlen("  . Marraskuu")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "  . Joulukuu", strlen("  . Joulukuu")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Maanantai", strlen("Maanantai")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Tiistai", strlen("Tiistai")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Keskiviikko", strlen("Keskiviikko")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Torstai", strlen("Torstai")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Perjantai", strlen("Perjantai")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Lauantai", strlen("Lauantai")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Sunnuntai", strlen("Sunnuntai")+1); // Sunday
        }
        
    } //END OF FINNISH
        break;
    case 'D': //DUTCH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   Januari", strlen("   Januari")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Februari", strlen("   Februari")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   Maart", strlen("   Maart")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   April", strlen("   April")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   Mei", strlen("   Mei")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   Juni", strlen("   Juni")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   Juli", strlen("   Juli")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   Augustus", strlen("   Augustus")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   September", strlen("   September")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   Oktober", strlen("   Oktober")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   November", strlen("   November")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   December", strlen("   December")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Maandag", strlen("Maandag")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Dinsdag", strlen("Dinsdag")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Woensdag", strlen("Woensdag")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Donderdag", strlen("Donderdag")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Vrijdag", strlen("Vrijdag")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Zaterdag", strlen("Zaterdag")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Zondag", strlen("Zondag")+1); // Sunday
        }
        
    } //END OF DUTCH
        break;
    case '1': //POLISH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   stycznia", strlen("   stycznia")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   lutego", strlen("   lutego")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   marca", strlen("   marca")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   kwietnia", strlen("   kwietnia")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   maja", strlen("   maja")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   czerwca", strlen("   czerwca")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   lipca", strlen("   lipca")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   sierpnia", strlen("   sierpnia")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   wrzesnia", strlen("   wrzesnia")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   pazdziernika", strlen("   pazdziernika")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   listopada", strlen("   listopada")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   grudnia", strlen("   grudnia")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Poniedzialek", strlen("Poniedzialek")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Wtorek", strlen("Wtorek")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Sroda", strlen("Sroda")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Czwartek", strlen("Czwartek")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Piątek", strlen("Piątek")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Sobota", strlen("Sobota")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Niedziela", strlen("Niedziela")+1); // Sunday
        }
        
    } //END OF POLISH
        break;
    case 'S': //SWEDISH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   Januari", strlen("   Januari")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Februari", strlen("   Februari")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   Mars", strlen("   Mars")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   April", strlen("   April")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   Maj", strlen("   Maj")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   Juni", strlen("   Juni")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   Juli", strlen("   Juli")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   Augusti", strlen("   Augusti")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   September", strlen("   September")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   Oktober", strlen("   Oktober")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   November", strlen("   November")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   December", strlen("   December")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Måndag", strlen("Måndag")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Tisdag", strlen("Tisdag")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Onsdag", strlen("Onsdag")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Torsdag", strlen("Torsdag")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Fredag", strlen("Fredag")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Lördag", strlen("Lördag")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Söndag ", strlen("Söndag ")+1); // Sunday
        }
        
    } //END OF SWEDISH
        break;
    case '2': //DANISH
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   . Januar", strlen("   . Januar")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   . Februar", strlen("   . Februar")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   . Marts", strlen("   . Marts")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   . April", strlen("   . April")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   . Maj", strlen("   . Maj")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   . Juni", strlen("   . Juni")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   . Juli", strlen("   . Juli")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   . August", strlen("   . August")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   . September", strlen("   . September")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   . Oktober", strlen("   . Oktober")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   . November", strlen("   . November")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   . December", strlen("   . December")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Mandag", strlen("Mandag")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Tirsdag", strlen("Tirsdag")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Onsdag", strlen("Onsdag")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Torsdag", strlen("Torsdag")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Fredag", strlen("Fredag")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Lørdag", strlen("Lørdag")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Søndag ", strlen("Søndag ")+1); // Sunday
        }
        
    } //END OF DANISH
        break;
    case '3': //CATALAN
    {
        translate_sp= true;
        
        if (month_text[0] == 'J' && month_text[1] == 'a')
        {
            memcpy(month_text, "   Gener", strlen("   Gener")+1); // January
        }
        else if (month_text[0] == 'F' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Febrer", strlen("   Febrer")+1); // Febrary
        }
        else if (month_text[0] == 'M' && month_text[2] == 'r')
        {
            memcpy(month_text, "   Març", strlen("   Març")+1); // March
        }
        else if (month_text[0] == 'A' && month_text[1] == 'p')
        {
            memcpy(month_text, "   Abril", strlen("   Abril")+1); // April
        }
        else if (month_text[0] == 'M' && month_text[2] == 'y')
        {
            memcpy(month_text, "   Maig", strlen("   Maig")+1); // May
        }
        else if (month_text[0] == 'J' && month_text[2] == 'n')
        {
            memcpy(month_text, "   Juny", strlen("   Juny")+1); // June
        }
        else if (month_text[0] == 'J' && month_text[2] == 'l')
        {
            memcpy(month_text, "   Juliol", strlen("   Juliol")+1); // July
        }
        else if (month_text[0] == 'A' && month_text[1] == 'u')
        {
            memcpy(month_text, "   Agost", strlen("   Agost")+1); // August
        }
        else if (month_text[0] == 'S' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Setembre", strlen("   Setembre")+1); // September
        }
        else if (month_text[0] == 'O' && month_text[1] == 'c')
        {
            memcpy(month_text, "   Octubre", strlen("   Octubre")+1); // October
        }
        else if (month_text[0] == 'N' && month_text[1] == 'o')
        {
            memcpy(month_text, "   Novembre", strlen("   Novembre")+1); // November
        }
        else if (month_text[0] == 'D' && month_text[1] == 'e')
        {
            memcpy(month_text, "   Desembre", strlen("   Desembre")+1); // December
        }
        
        // Primitive hack to translate the day of week to another language
        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
        // Supported characters: A-Z, a-z, 0-9
        if (weekday_text[0] == 'M')
        {
            memcpy(weekday_text, "Dilluns", strlen("Dilluns")+1); // Monday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Dimarts", strlen("Dimarts")+1); // Tuesday
        }
        else if (weekday_text[0] == 'W')
        {
            memcpy(weekday_text, "Dimecres", strlen("Dimecres")+1); // Wednesday
        }
        else if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
        {
            memcpy(weekday_text, "Dijous", strlen("Dijous")+1); // Thursday
        }
        else if (weekday_text[0] == 'F')
        {
            memcpy(weekday_text, "Divendres", strlen("Divendres")+1); // Friday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
        {
            memcpy(weekday_text, "Dissabte", strlen("Dissabte")+1); // Saturday
        }
        else if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
        {
            memcpy(weekday_text, "Diumenge ", strlen("Diumenge ")+1); // Sunday
        }
        
    } //END OF CATALAN
        break;
    default: 
    {
        translate_sp=false;
    } //If the language is not in the list of translations then keep english.
    }
    
    return translate_sp;
}