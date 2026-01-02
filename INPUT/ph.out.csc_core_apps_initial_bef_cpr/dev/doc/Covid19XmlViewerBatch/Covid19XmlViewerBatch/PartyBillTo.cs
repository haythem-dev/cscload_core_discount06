using System;
using System.Text;

namespace Covid19XmlViewerBatch
{
    static class PartyBillTo
    {
        static string BTPPartyIdIdent = "";
        static string BTPPartyIdPartnerNo = "";
        static string BTPName1 = "";
        static string BTPName2 = "";
        static string BTPName3 = "";
        static string BTPAdressID = "";
        static string BTPStreet = "";
        static string BTPDepartment = "";
        static string BTPPostalCode = "";
        static string BTPCity = "";
        static string BTPContactName = "";
        static string BTPContactMail = "";
        static string BTPContactPhone = "";
        static string BTPContactMobil = "";

        static public void DetermineValues(OrderPartyBillToParty party, string fileName, ref Logger Log)
        {
            try
            {
                BTPPartyIdIdent = party.Party.PartyID.Identifier.Ident;
                foreach (Identifier i in party.Party.ListOfIdentifier)
                {
                    if (i.Agency.AgencyCodedOther == "PartnerNumber")
                    {
                        BTPPartyIdPartnerNo = i.Ident;
                    }
                }
                BTPName1 = party.Party.NameAddress.Name1;
                BTPName2 = party.Party.NameAddress.Name2;
                BTPName3 = party.Party.NameAddress.Name3;
                BTPAdressID = party.Party.NameAddress.Identifier.Ident;
                BTPStreet = party.Party.NameAddress.Street;
                BTPDepartment = party.Party.NameAddress.Department;
                BTPPostalCode = party.Party.NameAddress.PostalCode;
                BTPCity = party.Party.NameAddress.City;
                BTPContactName = party.Party.OrderContact.Contact.ContactName;
                foreach (var x in party.Party.OrderContact.Contact.ListOfContactNumber)
                {
                    switch (x.ContactNumberTypeCoded)
                    {
                        case ContactNumberTypeCode.EmailAddress:
                            BTPContactMail = x.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.TelephoneNumber:
                            BTPContactPhone = x.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.MobileNumber:
                            BTPContactMobil = x.ContactNumberValue;
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Log($"File {fileName}: Fehler beim ermitteln von Details zur ShipToParty: {ex.Message}");
            }
        }

        static public void AddTitles(ref StringBuilder output)
        {
            output.Append("BillTo ID;");
            output.Append("BillTo PartnerNo;");
            output.Append("BillTo Name1;");
            output.Append("BillTo AdressID;");
            output.Append("BillTo Street;");
            output.Append("BillTo PLZ;");
            output.Append("BillTo City;");
            output.Append("BillTo Contact;");
            output.Append("BillTo Mail;");
            output.Append("BillTo Phone;");
            output.Append("BillTo Mobile;");
        }

        static public void AddValues(ref StringBuilder output)
        {
            output.Append($"{BTPPartyIdIdent};");
            output.Append($"{BTPPartyIdPartnerNo};");
            output.Append($"{BTPName1};");
            output.Append($"{BTPAdressID};");
            output.Append($"{BTPStreet};");
            output.Append($"{BTPPostalCode};");
            output.Append($"{BTPCity};");
            output.Append($"{BTPContactName};");
            output.Append($"Mail: {BTPContactMail};");
            output.Append($"Tel: {BTPContactPhone};");
            output.Append($"Mobil: {BTPContactMobil};");
        }

        static public void AddPartnerTitle(ref StringBuilder output)
        {
            output.Append("Partnernummer;");
        }
        static public void AddPartnerValue(ref StringBuilder output)
        {            
            output.Append($"{BTPPartyIdPartnerNo};");
        }

        static public void AddRechnungsadresseTitle(ref StringBuilder output)
        {
            output.Append("Rechnungsadresse;");
        }

        static public void AddRechnungsadresseValue(ref StringBuilder output)
        {
            output.Append("\"");
            output.Append($"Party-ID: {BTPPartyIdIdent}");
            output.Append($"\nAdress-ID: {BTPAdressID}");
            output.Append($"\nPartnernummer: {BTPPartyIdPartnerNo}");
            output.Append($"\n{BTPName1}");
            if (BTPName2.Trim().Length > 0) { output.Append($"\n{BTPName2}"); }
            if (BTPName3.Trim().Length > 0) { output.Append($"\n{BTPName3}"); }            
            if (BTPDepartment.Trim().Length > 0) { output.Append($"\n{BTPDepartment.Replace("\"", "'")}"); }
            if (BTPStreet.Trim().Length > 0) { output.Append($"\n{BTPStreet.Replace("\"", "'")}"); }
            if (BTPPostalCode.Trim().Length > 0 || BTPCity.Trim().Length > 0) { output.Append($"\n{BTPPostalCode} {BTPCity.Replace("\"", "'")}"); }            
            if (BTPContactPhone.Trim().Length > 0) { output.Append($"\nTel: {BTPContactPhone}"); }
            if (BTPContactMail.Trim().Length > 0) { output.Append($"\nE-Mail: {BTPContactMail}"); }                        
            output.Append("\";");
        }
    }
}
