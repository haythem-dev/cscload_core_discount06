
//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCallPlanEvents.h
   Author: A.Schmidt-Rehschuh
   made  : 27.07.2000
                            >No changes in this text may be made<
   declaration:

*/

#ifndef __PPCALLPLANEVENTS_H___123534_X12
#define __PPCALLPLANEVENTS_H___123534_X12

#include <assert.h>
#include <vector>

class ppCallPlanEvents
{
public:
    enum t_callstate { s_set                        = 0, /* Grundeinstellung */
                       s_customer_isbusy            = 1, /* Amtsleitung besetzt, Kunde nimmt nicht ab */
                       s_umk_isbusy                 = 2, /* keine Amtsleitung, Modem besetzt */
                       s_call_iscalled              = 3, /* Anruf ist in Arbeit */
                       s_reactivated                = 4, /* Anruf war ausgesteuert und wist wieder aktiviert */
                       s_delay                      = 5, /* verschoben von Anwender */
                       s_umk_disqualificated        = 7, /* ausgesteuert, weil x-mal keine Umkverbindung */
                       s_customer_disqualificated   = 8, /* ausgesteuert, weil kunde x-mal nicht erreicht */
                       s_call_isready               = 9, /* Anruf erledigt */
                       s_customer_inholiday         = 10,/* Apo. wegen Urlaub geschlossen */
                       s_holiday                    = 11 /* Feiertag */
    };

    enum t_cEvents { ce_set                     = 0, /* row is currently set (angelegt) */
                     ce_displace                = 1, /* Call was displaced  (verschoben) */
                     ce_deleted                 = 2, /* Call is deleted     (gelöscht) */
                     ce_no_order                = 3, /* today no order      (heute kein Auftrag) */
                     ce_transmitted             = 4, /* order transmitted    (übertragen) */
                     ce_order_already_available = 5, /* order already available (auftrag schon vorhanden) */
                     ce_fixed_tour              = 6, /* fixed tour assigned (feste Tour zugeordnet) */
                     ce_order_reactivated       = 7, /* order reactivated (Auftrag wieder in Rufplanabgestellt) */
                     ce_customer_iscalled       = 8, /* customer is called (Kunde wird angerufen) */
                     ce_call_set_to_free        = 9, /* calling again, problem with device (Hänger auf Modem) */
                     ce_call_finished           = 10,/* call correctly ended (Auftrag beendet) */
                     ce_call_finished_by_device = 11,/* call ended, but no response from umk */
                     ce_displaced_manuel        = 12,/* call is displaced by hand */
                     ce_empty_order             = 13,/* has no order taken from device (Verschieben wegen Leer-Auftrag)*/
                     ce_error_by_dafue          = 14,/* order reactivated (Abbruch bei Dafü)*/
                     ce_customer_disqualificated= 15,/* order is disqualificated (ausgesteuert) */
                     ce_call_is_already_called  = 16,/* That should never happen, only if the telephone call-plan is started with delay.*/
                     ce_call_not_ready          = 17,/* Customer did't provide his order */
                     ce_order_already_sended    = 18,/* order sended by customer */
                     ce_transfer_break          = 19,/* trannmission breaks by 99 */
                     ce_call_finished_by_plan   = 20,/* plan was stopped and startet forward at a new time; the callplan finish all calls before this time! */
                     ce_umk_error               = 21,/* umk sends wrong statement! */
                     ce_max_entry
    };

    enum t_callrecord   { r_datatransfer_parallel   = 0,
                          r_datatransfer_serial     = 1,
                          r_phonetic                = 2,
                          r_datatransfer_automatic  = 3,
                          r_end_of_list
    };

    enum t_calltime { call_rushorder    = 20, /* Eilauftrag */
                      call_not_later    = 30, /* Nicht nach der Rufzeit rufen */
                      call_punctual     = 40, /* pünktlich zur Rufzeit rufen */
                      call_not_early    = 50, /* nicht vorher rufen */
                      call_max          = 4
    };

protected: //constructor
    ppCallPlanEvents()
    {
        m_eEvent = ce_set;
        m_eCallTime = call_punctual;
        m_eCallState = s_set;
        //Priority of the calls
        m_vCallTime.clear();
        m_vCallTime.insert( m_vCallTime.end(), call_rushorder );
        m_vCallTime.insert( m_vCallTime.end(), call_not_later );
        m_vCallTime.insert( m_vCallTime.end(), call_punctual );
        m_vCallTime.insert( m_vCallTime.end(), call_not_early );
        m_ivCallTime = m_vCallTime.begin();

        m_straEvents[ce_set] = "angelegt";
        m_straEvents[ce_displace] = "verschoben";
        m_straEvents[ce_deleted] = "gelöscht";
        m_straEvents[ce_no_order] = "heute kein Auftrag";
        m_straEvents[ce_transmitted] = "gesendet";
        m_straEvents[ce_order_already_available] = "Auftrag schon vorhanden";
        m_straEvents[ce_fixed_tour] = "feste Tour zugeordnet";
        m_straEvents[ce_order_reactivated] = "Auftrag wieder in Rufplanabgestellt";
        m_straEvents[ce_customer_iscalled] = "Kunde wird angerufen";
        m_straEvents[ce_call_set_to_free] = "Problem mit Modem";
        m_straEvents[ce_call_finished] = "Auftrag gesendet";
        m_straEvents[ce_call_finished_by_device] = "Auftrag gesendet(kein umk)";
        m_straEvents[ce_displaced_manuel] = "verschoben von Anwender";
        m_straEvents[ce_empty_order] = "verschoben wegen leeren Auftrag";
        m_straEvents[ce_error_by_dafue] = "Abbruch bei Dafü";
        m_straEvents[ce_customer_disqualificated] = "Auftrag ausgesteuert (Kunde nicht erreicht)";
        m_straEvents[ce_call_is_already_called] = "Kunde wurde von anderem Modem gerade gerufen (frühere Ruf)";
        m_straEvents[ce_call_not_ready] = "Kunde hat Auftrag noch nicht bereitgestellt";
        m_straEvents[ce_order_already_sended] = "Kunde will Auftrag senden";
        m_straEvents[ce_transfer_break] = "99er Abbruch bei Dafü";
        m_straEvents[ce_call_finished_by_plan] = "Auftrag nicht gerufen, wegen technischer Probleme";
        m_straEvents[ce_umk_error] = "Umk-Fehler";

        m_strControlText[(call_rushorder/10) - 2] = "Eilauftrag";
        m_strControlText[(call_not_later/10) - 2] = "nicht später rufen";
        m_strControlText[(call_punctual/10) - 2] =  "pünktlich rufen";
        m_strControlText[(call_not_early/10) - 2] = "nicht vorher rufen";
        m_strCallInit = (long)call_punctual;
    }

public: //get posibilities (only numbers)

    const char* GetCallInit()
    {
        return m_strCallInit.c_str();
    }

    bool GetListCallControl(t_calltime& eCallTime)
    {
        if (m_ivCallTime == m_vCallTime.end())
        {
           m_ivCallTime = m_vCallTime.begin();
           return false;
        }

        eCallTime = *m_ivCallTime;
        m_ivCallTime++;
        return true;
    }

    //get posibilities (with text)
    bool GetListCallControl(ppString& strText)
    {
        if (m_ivCallTime == m_vCallTime.end())
        {
           m_ivCallTime = m_vCallTime.begin();
           return false;
        }

        strText = (long)*m_ivCallTime;
        strText += " ";
        strText += m_strControlText[(*m_ivCallTime/10) - 2];

        m_ivCallTime++;
        return true;
    }

    const char* GetEventMsg(const t_cEvents eEvent) const
    {
        assert(eEvent>= ce_set && eEvent < ce_max_entry);
        return m_straEvents[eEvent].c_str();
    }

public: //set/get-methodes
    virtual const t_cEvents GetEvent() const { return m_eEvent; }
    virtual void SetEvent(const t_cEvents eEvent)  { m_eEvent = eEvent; }
    virtual const t_calltime GetRufSteuerung() const { return m_eCallTime; }
    virtual void SetRufSteuerung(const t_calltime eCallTime) { m_eCallTime = eCallTime; }
    virtual const t_callstate GetAnrufStatus() const { return m_eCallState; }
    virtual void SetAnrufStatus( const t_callstate eCallState ) { m_eCallState = eCallState; }

protected: //members
    t_cEvents   m_eEvent;
    t_calltime  m_eCallTime;
    t_callstate m_eCallState;
    std::vector<t_calltime>             m_vCallTime;
    std::vector<t_calltime>::iterator   m_ivCallTime;
    ppString                        m_straEvents[ce_max_entry];
    ppString                        m_strControlText[call_max];
    ppString                        m_strCallInit;
};

#endif
