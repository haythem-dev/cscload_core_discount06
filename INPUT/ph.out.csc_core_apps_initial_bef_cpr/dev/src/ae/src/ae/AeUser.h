//Klasse zur Verwaltung eines Benutzerprofils
#include "aepwd.h"

class CAeUser
{
private:
    CAEPWD m_aepwd;
    CString m_Rechner;              //Rechner, von dem die Zugriffsrechte geholt wurden
    BOOL m_bInit;                   //User ist initialisiert (DB-Operationen moeglich)

public:
    CAeUser();                      //Konstruktor
    BOOL IsNoPasswd() { return strcmp(m_aepwd.s.PASSWORD, "dpC}OUKQ") == 0 ? TRUE : FALSE; }
    BOOL IsInit()     { return m_bInit; }

    AEPWD GetUser()         { return m_aepwd.s; }
    CString GetUserName()   { return m_aepwd.s.USERNAME; }
    CString GetPasswd()     { return m_aepwd.s.PASSWORD; }
    CString GetTermID()     { return m_aepwd.s.TERMID; }
    CString GetAgentID()    { return m_aepwd.s.AGENTID; }
    long GetUID()           { return m_aepwd.s.UID; }
    short GetUserBranchNo() { return m_aepwd.s.FILIALNR; }
    CString GetRechner()    { return m_Rechner; }
    short GetPoolID()       { return m_aepwd.s.POOLID; }
         
    void SetInit(BOOL bInit = TRUE)   { m_bInit = bInit; }
    void SetRechner(CString rechner)    { m_Rechner = rechner; }
    void SetUser(AEPWD aepwd)     { SetInit(); m_aepwd.s = aepwd; }
    void SetPasswd(CString passwd); //muss verschluesselt sein!!!
    void SetUIDAnlage(long uid)   { m_aepwd.s.UID_ANLAGE = uid; }
    void SetAgentId(CString agentId)    { AllgStrCopy(m_aepwd.s.AGENTID, agentId, L_AEPWD_AGENTID); }
    void SetPoolID(short poolID)  { m_aepwd.s.POOLID = poolID; }
         
    BOOL InitUser(CString userName, BOOL bMsg = FALSE); //User wird geladen
    void UpdateUserDB();          //Aendert Zugriffsrechte auf DB
    BOOL NewUserDB(CString Name, CString Password = "dpC}OUKQ"); //legt neuen User auf DB an (Def. UID und TERMID)
    void DeleteUserDB();          //Kennzeichnet einen User als inaktiv
    void InitPassword()           { SetPasswd("dpC}OUKQ"); } //Password neu initialisieren

    //Abfrage  AA-Rechte
    BOOL IsAeUser()                     { return IsBitSet(m_aepwd.s.AA[0]); }
    BOOL UpdParAuftrArt()               { return IsBitSet(m_aepwd.s.AA[1]); }
    BOOL UpdParKommArt()                { return IsBitSet(m_aepwd.s.AA[2]); }
    BOOL UpdParBuchArt()                { return IsBitSet(m_aepwd.s.AA[3]); }
    BOOL UpdParKaBaKomb()               { return IsBitSet(m_aepwd.s.AA[4]); }
    BOOL UpdParKondGr()                 { return IsBitSet(m_aepwd.s.AA[5]); }
    BOOL UpdParAufBearb()               { return IsBitSet(m_aepwd.s.AA[6]); }
    BOOL UpdParAufBeErg()               { return IsBitSet(m_aepwd.s.AA[7]); }
    BOOL UpdParKommi()                  { return IsBitSet(m_aepwd.s.AA[8]); }
    BOOL UpdParNachrArten()             { return IsBitSet(m_aepwd.s.AA[9]); }
    BOOL UpdParKomBehTyp()              { return IsBitSet(m_aepwd.s.AA[10]); }
    BOOL IsErwKndInfo()                 { return IsBitSet(m_aepwd.s.AA[11]); }
    BOOL IsErfasAndereFiliale()         { return IsBitSet(m_aepwd.s.AA[12]); }
    BOOL IsAdminAndereFiliale()         { return IsBitSet(m_aepwd.s.AA[13]); }
    BOOL UpdUser()                      { return IsBitSet(m_aepwd.s.AA[14]); }
    BOOL UpdTour()                      { return IsBitSet(m_aepwd.s.AA[15]); }
    BOOL UpdInfo()                      { return IsBitSet(m_aepwd.s.AA[16]); }
    BOOL UpdAltfil()                    { return IsBitSet(m_aepwd.s.AA[17]); }
    BOOL UpdZeitart()                   { return IsBitSet(m_aepwd.s.AA[18]); }
    BOOL UpdEntsperr()                  { return IsBitSet(m_aepwd.s.AA[19]); }
    BOOL UpdRufpAbw()                   { return IsBitSet(m_aepwd.s.AA[20]); }
    BOOL UpdKndAufArt()                 { return IsBitSet(m_aepwd.s.AA[21]); }
    BOOL AnzFilialUms()                 { return IsBitSet(m_aepwd.s.AA[22]); }
    BOOL Planteil()                     { return IsBitSet(m_aepwd.s.AA[23]); }
    BOOL DirektPZN()                    { return IsBitSet(m_aepwd.s.AA[24]); }
    BOOL UpdCallback()                  { return IsBitSet(m_aepwd.s.AA[25]); }
    BOOL ChangeFiliale()                { return IsBitSet(m_aepwd.s.AA[26]); }
    BOOL StatusErl()                    { return IsBitSet(m_aepwd.s.AA[27]); }
    BOOL UpdSeraPlan()                  { return IsBitSet(m_aepwd.s.AA[28]); }
    BOOL IsAnzAuf()                     { return IsBitSet(m_aepwd.s.AA[29]); }
    BOOL IsSperreAe()                   { return IsBitSet(m_aepwd.s.AA[30]); }
    BOOL IsInfoListe()                  { return IsBitSet(m_aepwd.s.AA[31]); }
    BOOL UpdMailUser()                  { return IsBitSet(m_aepwd.s.AA[32]); }
    BOOL IsMessage()                    { return IsBitSet(m_aepwd.s.AA[33]); }
    BOOL UpdModem()                     { return IsBitSet(m_aepwd.s.AA[34]); }
    BOOL IsMehrVz()                     { return IsBitSet(m_aepwd.s.AA[35]); }
    BOOL Anrufplanuebernahme()          { return IsBitSet(m_aepwd.s.AA[36]); }
    BOOL Regionenverwalten()            { return IsBitSet(m_aepwd.s.AA[37]); }
    BOOL Feiertage()                    { return IsBitSet(m_aepwd.s.AA[38]); }
    BOOL Bewegungen()                   { return IsBitSet(m_aepwd.s.AA[39]); }
    BOOL KeinPlan()                     { return IsBitSet(m_aepwd.s.AA[40]); }
    BOOL DispoBearb()                   { return IsBitSet(m_aepwd.s.AA[41]); }
    BOOL DispoRechte()                  { return IsBitSet(m_aepwd.s.AA[42]); }
    BOOL DispoDoku()                    { return IsBitSet(m_aepwd.s.AA[43]); }
    BOOL IsHiPathUser()                 { return IsBitSet(m_aepwd.s.AA[44]); }
    BOOL IsInfoPflege()                 { return IsBitSet(m_aepwd.s.AA[45]); }
    BOOL IsVorausPflege()               { return IsBitSet(m_aepwd.s.AA[46]); }
    BOOL IsKreditAbschluss()            { return IsBitSet(m_aepwd.s.AA[47]); }
    BOOL IsInternetAbschluss()          { return IsBitSet(m_aepwd.s.AA[48]); }
    BOOL IsPflegeReserve()              { return IsBitSet(m_aepwd.s.AA[49]); }
    BOOL IsAbschlussBTM()               { return IsBitSet(m_aepwd.s.AA2[0]); }
    BOOL IsAdminCustGrps()              { return IsBitSet(m_aepwd.s.AA2[1]); }
    BOOL IsPflegeNotfall()              { return IsBitSet(m_aepwd.s.AA2[2]); }
    BOOL IsPflegeCountry()              { return IsBitSet(m_aepwd.s.AA2[3]); }
    BOOL IsPflegeRufweiter()            { return IsBitSet(m_aepwd.s.AA2[4]); }
    BOOL IsPflegeQuota()                { return IsBitSet(m_aepwd.s.AA2[5]); }
    BOOL IsPflegeDD()                   { return IsBitSet(m_aepwd.s.AA2[6]); }
    BOOL IsPflegeBranchInfo()           { return IsBitSet(m_aepwd.s.AA2[7]); }
    BOOL IsPflegeForbidden()            { return IsBitSet(m_aepwd.s.AA2[8]); }
    BOOL IsPflegeSeparat()              { return IsBitSet(m_aepwd.s.AA2[9]); }
    BOOL IsPflegeVAIdf()                { return IsBitSet(m_aepwd.s.AA2[10]); }
    BOOL IsFreePrice()                  { return IsBitSet(m_aepwd.s.AA2[11]); }
    BOOL IsDiscountUp()                 { return IsBitSet(m_aepwd.s.AA2[12]); }
    BOOL IsBeilageUp()                  { return IsBitSet(m_aepwd.s.AA2[13]); }
    BOOL IsPflegeReserveZert()          { return IsBitSet(m_aepwd.s.AA2[14]); }
    BOOL IsPflegeReserveBPZ()           { return IsBitSet(m_aepwd.s.AA2[15]); }
    BOOL IsEinzelhandelApo()            { return IsBitSet(m_aepwd.s.AA2[16]); }
    BOOL IsCheckPickingChange()         { return IsBitSet(m_aepwd.s.AA2[17]); }
    BOOL IsUserInfoVz()                 { return IsBitSet(m_aepwd.s.AA2[18]); }
    BOOL IsUserInfoAll()                { return IsBitSet(m_aepwd.s.AA2[19]); }
    BOOL IsDealerInfoAll()              { return IsBitSet(m_aepwd.s.AA2[20]); }
    BOOL IsPflegeEncloser()             { return IsBitSet(m_aepwd.s.AA2[21]); }
    BOOL IsOnlyInfo()                   { return IsBitSet(m_aepwd.s.AA2[22]); }
    BOOL IsPflegeReserveCharge()        { return IsBitSet(m_aepwd.s.AA2[23]); }
    BOOL IsChangeRebateCalc()           { return IsBitSet(m_aepwd.s.AA2[24]); }
    BOOL IsChangeDPODays()              { return IsBitSet(m_aepwd.s.AA2[25]); }
    BOOL IsMSV3bearb()                  { return IsBitSet(m_aepwd.s.AA2[26]); }
    BOOL IsPflegeOrigintypesettings()   { return IsBitSet(m_aepwd.s.AA2[27]); }
    BOOL IsPflegeCremaMailAdr()         { return IsBitSet(m_aepwd.s.AA2[28]); }
    BOOL IsStornoCremaOrder()           { return IsBitSet(m_aepwd.s.AA2[29]); }
    BOOL IsMSV3bearbNo()                { return IsBitSet(m_aepwd.s.AA2[30]); }
    BOOL Is2ndLevel()                   { return IsBitSet(m_aepwd.s.AA2[31]); }
    BOOL IsPflegeCBRemarks()            { return IsBitSet(m_aepwd.s.AA2[32]); }
    BOOL IsPflegeCstTours()             { return IsBitSet(m_aepwd.s.AA2[33]); }
    BOOL IsPflegeExtraTourReasons()     { return IsBitSet(m_aepwd.s.AA2[34]); }
    BOOL IsPflegeBestellFenster()       { return IsBitSet(m_aepwd.s.AA2[35]); }
    BOOL IsCremaChangeTour()            { return IsBitSet(m_aepwd.s.AA2[36]); }
    BOOL IsPflegeReservationConfig()    { return IsBitSet(m_aepwd.s.AA2[37]); }
    BOOL IsPflegeCSVImportParam()       { return IsBitSet(m_aepwd.s.AA2[38]); }
    BOOL IsCSVImport()                  { return IsBitSet(m_aepwd.s.AA2[39]); }
    BOOL IsDEGetter()                   { return IsBitSet(m_aepwd.s.AA2[40]); }
    BOOL IsAnzLief()                    { return IsBitSet(m_aepwd.s.AA2[41]); }
    BOOL IsAnzRech()                    { return IsBitSet(m_aepwd.s.AA2[42]); }
    BOOL IsEnableWerbeFach()            { return IsBitSet(m_aepwd.s.AA2[43]); }
    BOOL IsShowParamChanges()           { return IsBitSet(m_aepwd.s.AA2[44]); }
    BOOL IsAbleToChangeCMIOrder()       { return IsBitSet(m_aepwd.s.AA2[45]); }
    BOOL DispoHinttext()                { return IsBitSet(m_aepwd.s.AA2[46]); }

    //Setzen  AA-Rechte
    void SetIsAeUser(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[0], b); }
    void SetUpdParAuftrArt(BOOL b=TRUE)             { SetBit(m_aepwd.s.AA[1], b); }
    void SetUpdParKommArt(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA[2], b); }
    void SetUpdParBuchArt(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA[3], b); }
    void SetParKaBaKomb(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[4], b); }
    void SetParKondGr(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[5], b); }
    void SetParAufBearb(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[6], b); }
    void SetParAufBeErg(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[7], b); }
    void SetParKommi(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[8], b); }
    void SetUpdParNachrArten(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA[9], b); }
    void SetUpdParKomBehTyp(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA[10], b); }
    void SetIsErwKndInfo(BOOL b = TRUE)             { SetBit(m_aepwd.s.AA[11], b); }
    void SetIsErfasAndereFiliale(BOOL b = TRUE)     { SetBit(m_aepwd.s.AA[12], b); }
    void SetIsAdminAndereFiliale(BOOL b = TRUE)     { SetBit(m_aepwd.s.AA[13], b); }
    void SetUpdUser(BOOL b = TRUE)                  { SetBit(m_aepwd.s.AA[14], b); }
    void SetUpdTour(BOOL b = TRUE)                  { SetBit(m_aepwd.s.AA[15], b); }
    void SetUpdInfo(BOOL b = TRUE)                  { SetBit(m_aepwd.s.AA[16], b); }
    void SetUpdAltfil(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[17], b); }
    void SetUpdZeitart(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[18], b); }
    void SetUpdEntsperr(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[19], b); }
    void SetUpdRufpAbw(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[20], b); }
    void SetUpdKndAufArt(BOOL b = TRUE)             { SetBit(m_aepwd.s.AA[21], b); }
    void SetAnzFilialUms(BOOL b = TRUE)             { SetBit(m_aepwd.s.AA[22], b); }
    void SetPlanteil(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[23], b); }
    void SetDirektPZN(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[24], b); }
    void SetUpdCallback(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[25], b); }
    void SetChangeFiliale(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA[26], b); }
    void SetStatusErl(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[27], b); }
    void SetUpdSeraPlan(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[28], b); }
    void SetIsAnzAuf(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[29], b); }
    void SetIsSperreAe(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[30], b); }
    void SetIsInfoListe(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[31], b); }
    void SetUpdMailUser(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[32], b); }
    void SetIsMessage(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[33], b); }
    void SetUpdModem(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[34], b); }
    void SetIsMehrVz(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[35], b); }
    void SetAnrufplanuebernahme(BOOL b = TRUE)      { SetBit(m_aepwd.s.AA[36], b); }
    void SetRegionenverwalten(BOOL b = TRUE)        { SetBit(m_aepwd.s.AA[37], b); }
    void SetFeiertage(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[38], b); }
    void SetBewegungen(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[39], b); }
    void SetKeinPlan(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA[40], b); }
    void SetDispoBearb(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[41], b); }
    void SetDispoRechte(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA[42], b); }
    void SetDispoDoku(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA[43], b); }
    void SetHiPathUser(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[44], b); }
    void SetInfoPflege(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA[45], b); }
    void SetVorausPflege(BOOL b = TRUE)             { SetBit(m_aepwd.s.AA[46], b); }
    void SetKreditAbschluss(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA[47], b); }
    void SetInternetAbschluss(BOOL b = TRUE)        { SetBit(m_aepwd.s.AA[48], b); }
    void SetPflegeReserve(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA[49], b); }
    void SetAbschlussBTM(BOOL b = TRUE)             { SetBit(m_aepwd.s.AA2[0], b); }
    void SetAdminCustGrps(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[1], b); }
    void SetPflegeNotfall(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[2], b); }
    void SetPflegeCountry(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[3], b); }
    void SetPflegeRufweiter(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[4], b); }
    void SetPflegeQuota(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA2[5], b); }
    void SetPflegeDD(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA2[6], b); }
    void SetPflegeBranchInfo(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA2[7], b); }
    void SetPflegeForbidden(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[8], b); }
    void SetPflegeSeparat(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[9], b); }
    void SetPflegeVAIdf(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA2[10], b); }
    void SetFreePrice(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA2[11], b); }
    void SetDiscountUp(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA2[12], b); }
    void SetBeilageUp(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA2[13], b); }
    void SetPflegeReserveZert(BOOL b = TRUE)        { SetBit(m_aepwd.s.AA2[14], b); }
    void SetPflegeReserveBPZ(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA2[15], b); }
    void SetEinzelhandelApo(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[16], b); }
    void SetCheckPickingChange(BOOL b = TRUE)       { SetBit(m_aepwd.s.AA2[17], b); }
    void SetUserInfoVz(BOOL b = TRUE)               { SetBit(m_aepwd.s.AA2[18], b); }
    void SetUserInfoAll(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA2[19], b); }
    void SetDealerInfoAll(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[20], b); }
    void SetPflegeEncloser(BOOL b = TRUE)           { SetBit(m_aepwd.s.AA2[21], b); }
    void SetOnlyInfo(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA2[22], b); }
    void SetPflegeReserveCharge(BOOL b = TRUE)      { SetBit(m_aepwd.s.AA2[23], b); }
    void SetChangeRebateCalc(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA2[24], b); }
    void SetChangeDPODays(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[25], b); }
    void SetMSV3bearb(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA2[26], b); }
    void SetPflegeOrigintypesettings(BOOL b = TRUE) { SetBit(m_aepwd.s.AA2[27], b); }
    void SetPflegeCremaMailAdr(BOOL b = TRUE)       { SetBit(m_aepwd.s.AA2[28], b); }
    void SetStornoCremaOrder(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA2[29], b); }
    void SetMSV3bearbNo(BOOL b = TRUE)              { SetBit(m_aepwd.s.AA2[30], b); }
    void Set2ndLevel(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA2[31], b); }
    void SetPflegeCBRemarks(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[32], b); }
    void SetPflegeCstTours(BOOL b = TRUE)           { SetBit(m_aepwd.s.AA2[33], b); }
    void SetPflegeExtraTourReasons(BOOL b = TRUE)   { SetBit(m_aepwd.s.AA2[34], b); }
    void SetPflegeBestellFenster(BOOL b = TRUE)     { SetBit(m_aepwd.s.AA2[35], b); }
    void SetCremaChangeTour(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[36], b); }
    void SetPflegeReservationConfig(BOOL b = TRUE)  { SetBit(m_aepwd.s.AA2[37], b); }
    void SetPflegeCSVImportParam(BOOL b = TRUE)     { SetBit(m_aepwd.s.AA2[38], b); }
    void SetCSVImport(BOOL b = TRUE)                { SetBit(m_aepwd.s.AA2[39], b); }
    void SetDEGetter(BOOL b = TRUE)                 { SetBit(m_aepwd.s.AA2[40], b); }
    void SetAnzLief(BOOL b = TRUE)                  { SetBit(m_aepwd.s.AA2[41], b); }
    void SetAnzRech(BOOL b = TRUE)                  { SetBit(m_aepwd.s.AA2[42], b); }
    void SetEnableWerbeFach(BOOL b = TRUE)          { SetBit(m_aepwd.s.AA2[43], b); }
    void SetShowParamChanges(BOOL b = TRUE)         { SetBit(m_aepwd.s.AA2[44], b); }
    void SetAbleToChangeCMIOrder(BOOL b = TRUE)     { SetBit(m_aepwd.s.AA2[45], b); }
    void SetDispoHinttext(BOOL b = TRUE)            { SetBit(m_aepwd.s.AA2[46], b); }

private:
    void SetBit(char& aa, BOOL b);
    BOOL IsBitSet(const char& aa) const;
};
