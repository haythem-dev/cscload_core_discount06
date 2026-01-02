using System;
using System.Text;

namespace Covid19XmlViewerBatch
{
    static class PartySeller
    {
        static string SPPartyIdIdent = "";
        static string SPPartyVatId = "";
        static string SPName1 = "";
        static string SPName2 = "";
        static string SPName3 = "";
        static string SPStreet = "";
        static string SPPostalCode = "";
        static string SPCity = "";
        static string SPOrderContactEmail = "";
        static string SPOrderContactPhone = "";
        static string SPOrderContactFax = "";

        static public void DetermineValues(OrderPartySellerParty party, string fileName, ref Logger Log)
        {
            try
            {                
                SPPartyIdIdent = party.Party.PartyID.Identifier.Ident;
                foreach (Identifier i in party.Party.ListOfIdentifier)
                {
                    if (i.Agency.AgencyCodedOther == "VAT-ID")
                    {
                        SPPartyVatId = i.Ident;
                    }
                }
                SPName1 = party.Party.NameAddress.Name1;
                SPName2 = party.Party.NameAddress.Name2;
                SPName3 = party.Party.NameAddress.Name3;
                SPStreet = party.Party.NameAddress.Street;
                SPPostalCode = party.Party.NameAddress.PostalCode;
                SPCity = party.Party.NameAddress.City;

                foreach (ContactNumber cn in party.Party.OrderContact.Contact.ListOfContactNumber)
                {
                    switch (cn.ContactNumberTypeCoded)
                    {
                        case ContactNumberTypeCode.EmailAddress:
                            SPOrderContactEmail = cn.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.TelephoneNumber:
                            SPOrderContactPhone = cn.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.FaxNumber:
                            SPOrderContactFax = cn.ContactNumberValue;
                            break;
                        default:
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Log($"File {fileName}: Fehler beim ermitteln von Details zur SellerParty: {ex.Message}");
            }
        }

        static public void AddTitles( ref StringBuilder output )
        {
            output.Append("Seller ID;");
            output.Append("Seller VAT-ID;");
            output.Append("Seller Name1;");
            output.Append("Seller Name2;");
            output.Append("Seller Name3;");
            output.Append("Seller Street;");
            output.Append("Seller PLZ;");
            output.Append("Seller City;");
            output.Append("Seller Mail;");
            output.Append("Seller Phone;");
            output.Append("Seller Fax;");
        }

        static public void AddValues(ref StringBuilder output)
        {
            output.Append($"{SPPartyIdIdent};");
            output.Append($"{SPPartyVatId};");
            output.Append($"{SPName1};");
            output.Append($"{SPName2};");
            output.Append($"{SPName3};");
            output.Append($"{SPStreet};");
            output.Append($"{SPPostalCode};");
            output.Append($"{SPCity};");
            output.Append($"Mail: {SPOrderContactEmail};");
            output.Append($"Tel: {SPOrderContactPhone};");
            output.Append($"Fax: {SPOrderContactFax};");
        }
    }
}
