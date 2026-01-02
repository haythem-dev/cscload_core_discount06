using System;
using System.Text;

namespace Covid19XmlViewerBatch
{
    static class PartyBuyer
    {
        static string BPPartyIdIdent = "";
        static string BPName1 = "";
        static string BPName2 = "";
        static string BPName3 = "";
        static string BPOrderContactName = "";
        static string BPOrderContactEmail = "";
        static string BPOrderContactPhone = "";
        static string BPOrderContactMobil = "";

        static public void DetermineValues(OrderPartyBuyerParty buyerParty, string fileName, ref Logger Log)
        {
            try
            {                
                BPPartyIdIdent = buyerParty.Party.PartyID.Identifier.Ident;
                BPName1 = buyerParty.Party.NameAddress.Name1;
                BPName2 = buyerParty.Party.NameAddress.Name2;
                BPName3 = buyerParty.Party.NameAddress.Name3;
                BPOrderContactName = buyerParty.Party.OrderContact.Contact.ContactName;
                foreach (ContactNumber cn in buyerParty.Party.OrderContact.Contact.ListOfContactNumber)
                {
                    switch (cn.ContactNumberTypeCoded)
                    {
                        case ContactNumberTypeCode.EmailAddress:
                            BPOrderContactEmail = cn.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.TelephoneNumber:
                            BPOrderContactPhone = cn.ContactNumberValue;
                            break;
                        case ContactNumberTypeCode.MobileNumber:
                            BPOrderContactMobil = cn.ContactNumberValue;
                            break;
                        default:
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.Log($"File {fileName}: Fehler beim ermitteln von Details zur BuyerParty: {ex.Message}");
            }
        }

        static public void AddTitles( ref StringBuilder output )
        {
            output.Append("Buyer ID;");
            output.Append("Buyer Name1;");
            output.Append("Buyer Name2;");
            output.Append("Buyer Name3;");
            output.Append("Buyer Contact;");
            output.Append("Buyer Mail;");
            output.Append("Buyer Phone;");
            output.Append("Buyer Mobile;");
        }

        static public void AddValues( ref StringBuilder output )
        {
            output.Append($"{BPPartyIdIdent};");
            output.Append($"{BPName1};");
            output.Append($"{BPName2};");
            output.Append($"{BPName3};");
            output.Append($"{BPOrderContactName};");
            output.Append($"Mail: {BPOrderContactEmail};");
            output.Append($"Tel: {BPOrderContactPhone};");
            output.Append($"Mobile: {BPOrderContactMobil};");
        }

        static public void AddKaeuferTitle(ref StringBuilder output)
        {
            output.Append("Käufer;");
        }

        static public void AddKaeuferValues(ref StringBuilder output)
        {
            output.Append("\"");
            output.Append($"{BPOrderContactName}");
            if (BPOrderContactPhone.Trim().Length > 0) { output.Append($"\nTel: {BPOrderContactPhone}"); }            
            if (BPOrderContactMobil.Trim().Length > 0) { output.Append($"\nMobil: {BPOrderContactMobil}"); }            
            if (BPOrderContactEmail.Trim().Length > 0) { output.Append($"\nMail: {BPOrderContactEmail}"); }
            output.Append("\";");
        }
    }
}
