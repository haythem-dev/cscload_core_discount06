using System;
using System.Text;

namespace Covid19XmlViewerBatch
{
    static class PartyShipTo
    {
        static string STPPartyIdIdent = "";
        static string STPName1 = "";
        static string STPName2 = "";
        static string STPName3 = "";
        static string STPAdressID = "";
        static string STPStreet = "";        
        static string STPBuilding = "";
        static string STPRoomNo = "";
        static string STPInhouseMail = "";
        static string STPRegion = "";        
        static string STPDepartment = "";
        static string STPPostalCode = "";
        static string STPCity = "";
        static string STPContactName = "";
        static string STPContactMail = "";
        static string STPContactPhone = "";
        static string STPReceivingContactName = "";
        static string STPShippingContactName = "";
        static string STPCountry = "";

        static public void DetermineValues(OrderPartyShipToParty party, string fileName, ref Logger Log)
        {
            try
            {                
                STPPartyIdIdent = party.Party.PartyID.Identifier.Ident;                
                STPName1 = party.Party.NameAddress.Name1;
                STPName2 = party.Party.NameAddress.Name2;
                STPName3 = party.Party.NameAddress.Name3;
                STPAdressID = party.Party.NameAddress.Identifier.Ident;
                STPStreet = party.Party.NameAddress.Street;

                STPBuilding = party.Party.NameAddress.Building;
                STPRoomNo = party.Party.NameAddress.RoomNumber;
                STPInhouseMail = party.Party.NameAddress.InhouseMail;
                STPRegion = party.Party.NameAddress.Region.RegionCodedOther;

                STPDepartment = party.Party.NameAddress.Department;
                STPPostalCode = party.Party.NameAddress.PostalCode;
                STPCity = party.Party.NameAddress.City;
                STPContactName = party.Party.OrderContact.Contact.ContactName;
                STPReceivingContactName = party.Party.ReceivingContact.Contact.ContactName;
                STPShippingContactName = party.Party.ShippingContact.Contact.ContactName;

                STPCountry = party.Party.NameAddress.Country.CountryCoded.ToString();

                foreach (ContactNumber cn in party.Party.OrderContact.Contact.ListOfContactNumber)
                {
                    switch (cn.ContactNumberTypeCoded)
                    {
                        case ContactNumberTypeCode.EmailAddress:
                            STPContactMail = cn.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.TelephoneNumber:
                            STPContactPhone = cn.ContactNumberValue;
                            break;
                        default:
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Log($"File {fileName}: Fehler beim ermitteln von Details zur ShipToParty: {ex.Message}");
            }
        }

        static public void AddTitles( ref StringBuilder output )
        {
            output.Append("ShipTo ID;");
            output.Append("ShipTo Name1;");
            output.Append("ShipTo Name2;");
            output.Append("ShipTo Name3;");
            output.Append("ShipTo AddressID;");
            output.Append("ShipTo Street;");
            output.Append("ShipTo InhouseMail;");
            output.Append("ShipTo Region;");
            output.Append("ShipTo Abteilung;");
            output.Append("ShipTo PLZ;");
            output.Append("ShipTo City;");
            output.Append("ShipTo Contact;");
            output.Append("ShipTo Contact Mail;");
            output.Append("ShipTo Contact Phone;");
            output.Append("ShipTo ReceivingContact;");
            output.Append("ShipTo ShippingContact;");            
        }        

        static public void AddValues( ref StringBuilder output )
        {
            output.Append($"{STPPartyIdIdent};");
            output.Append($"{STPName1};");
            output.Append($"{STPName2};");
            output.Append($"{STPName3};");
            output.Append($"{STPAdressID};");
            output.Append($"{STPStreet};");
            output.Append($"{STPInhouseMail};");
            output.Append($"{STPRegion};");
            output.Append($"{STPDepartment};");
            output.Append($"{STPPostalCode};");
            output.Append($"{STPCity};");
            output.Append($"{STPContactName};");
            output.Append($"Mail: {STPContactMail};");
            output.Append($"Tel: {STPContactPhone};");
            output.Append($"{STPReceivingContactName};");
            output.Append($"{STPShippingContactName};");
        }

        static public void AddLieferadresseTitle(ref StringBuilder output)
        {
            output.Append("Lieferadresse;");
        }

        static public void AddLieferadresseValues(ref StringBuilder output)
        {
            output.Append("\"");
            output.Append($"{STPName1.Replace("\"","'")}");
            if (STPName2.Trim().Length > 0) { output.Append($"\n{STPName2.Replace("\"", "'")}"); }
            if (STPName3.Trim().Length > 0) { output.Append($"\n{STPName3.Replace("\"", "'")}"); }
            if (STPBuilding.Trim().Length > 0) { output.Append($"\n{STPBuilding.Replace("\"", "'")}"); }
            if (STPRoomNo.Trim().Length > 0) { output.Append($"\n{STPRoomNo.Replace("\"", "'")}"); }
            if (STPInhouseMail.Trim().Length > 0) { output.Append($"\n{STPInhouseMail.Replace("\"", "'")}"); }
            if (STPDepartment.Trim().Length > 0) { output.Append($"\n{STPDepartment.Replace("\"", "'")}"); }
            if (STPStreet.Trim().Length > 0) { output.Append($"\n{STPStreet.Replace("\"", "'")}"); }
            if (STPPostalCode.Trim().Length > 0 || STPCity.Trim().Length > 0) { output.Append($"\n{STPPostalCode} {STPCity.Replace("\"", "'")}"); }
            if (STPRegion.Trim().Length > 0) { output.Append($"\n{STPRegion.Replace("\"", "'")}"); }
            if (STPContactPhone.Trim().Length > 0) { output.Append($"\nTel: {STPContactPhone}"); }
            if (STPContactMail.Trim().Length > 0) { output.Append($"\nE-Mail: {STPContactMail}"); }
            if (STPCountry.Trim().Length > 0) { output.Append($"\n{STPCountry}"); }
            output.Append("\";");
        }


        static public void AddLieferadresseColumnTitles(ref StringBuilder output)
        {
            output.Append("AdressID;");
            output.Append("Name1;");
            output.Append("Name2;");
            output.Append("Name3;");
            output.Append("Street;");
            output.Append("PostalCode;");
            output.Append("City;");            
            output.Append("Telephone;");
            output.Append("Mail;");
            output.Append("Country;");
            output.Append("Region;");
            output.Append("Building;");
            output.Append("RoomNo;");
            output.Append("InhouseMail;");
            output.Append("Department;");
        }

        static public void AddLieferadresseColumns(ref StringBuilder output)
        {
            output.Append($"\"{STPAdressID.Replace("\"", "'")}\";"); // AdressID
            output.Append($"\"{STPName1.Replace("\"", "'")}\";"); // Name1
            output.Append($"\"{STPName2.Replace("\"", "'")}\";"); // Name2
            output.Append($"\"{STPName3.Replace("\"", "'")}\";"); // Name3       
            output.Append($"\"{STPStreet.Replace("\"", "'")}\";"); // Street
            output.Append($"\"{STPPostalCode.Replace("\"", "'")}\";"); // PostalCode
            output.Append($"\"{STPCity.Replace("\"", "'")}\";"); // City
            output.Append($"\" {STPContactPhone.Replace("\"", "'")}\";"); // Telephone
            output.Append($"\"{STPContactMail.Replace("\"", "'")}\";"); // eMail
            output.Append($"\"{STPCountry.Replace("\"", "'")}\";"); // Country                      
            output.Append($"\"{STPRegion.Replace("\"", "'")}\";"); // Region                                         
            output.Append($"\"{STPBuilding.Replace("\"", "'")}\";"); // Building            
            output.Append($"\"{STPRoomNo.Replace("\"", "'")}\";"); // RoomNo    
            output.Append($"\"{STPInhouseMail.Replace("\"", "'")}\";"); // InhouseMail
            output.Append($"\"{STPDepartment.Replace("\"", "'")}\";"); // Department            
        }

    }
}
