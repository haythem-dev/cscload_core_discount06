#ifndef SQL_REQS_H_INCLUDED
#define SQL_REQS_H_INCLUDED

    /* Prepare "select join" to get distinct ocp_article_no from (cocp_stagein_articlecode, cocp_stagein_article, cocp_stagein_articleprice, cocp_stagein_article_france) */
#define PSQL_STR_SEL_OCPNO_COCP_STAGEIN_XXX_IMPORT_DATETIME(str) strcpy(str, "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articlecode ");\
    strcat(str, " WHERE import_date = ? and import_time = ?");\
    strcat(str, " UNION ");\
    strcat(str, " (SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article ");\
    strcat(str, " WHERE import_date = ? and import_time = ?)");\
    strcat(str, " UNION ");\
    strcat(str, " (SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articleprice ");\
    strcat(str, " WHERE import_date = ? and import_time = ?)");\
    strcat(str, " UNION ");\
    strcat(str, " (SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article_france ");\
    strcat(str, " WHERE import_date = ? and import_time = ?)");


    /* Prepare Insert/update/delete in cocp_stagein_articlecode */
#define PSQL_STR_INS_COCP_STAGEIN_ARTICLECODE(str) strcpy(str, "INSERT into cocp_stagein_articlecode (");\
    strcat(str, " import_date");\
    strcat(str, ",import_time");\
    strcat(str, ",ocp_article_no");\
    strcat(str, ",code_type");\
    strcat(str, ",article_code");\
    strcat(str, ",preferred_flag");\
    strcat(str, ",changed_date");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ? )");

#define PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLECODE(str) strcpy(str, "DELETE from cocp_stagein_articlecode ");\
    strcat(str, " where ocp_article_no = ? and ((import_date < ?) or (import_date = ? and import_time < ? ))");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLECODE(str) strcpy(str, "DELETE from cocp_stagein_articlecode ");\
    strcat(str, " where ocp_article_no = ? and import_date = ? and import_time = ? ");

    /* Prepare Insert/update/delete in cocp_stagein_article */
#define PSQL_STR_INS_COCP_STAGEIN_ARTICLE(str) strcpy(str, "INSERT into cocp_stagein_article (");\
    strcat(str, " import_date");\
    strcat(str, ",import_time");\
    strcat(str, ",ocp_article_no");\
    strcat(str, ",long_name");\
    strcat(str, ",unit");\
    strcat(str, ",dosage_form");\
    strcat(str, ",product_group");\
    strcat(str, ",product_type");\
    strcat(str, ",manufacturer_no");\
    strcat(str, ",supplier_no");\
    strcat(str, ",length");\
    strcat(str, ",width");\
    strcat(str, ",height");\
    strcat(str, ",weight");\
    strcat(str, ",package_unit_1");\
    strcat(str, ",package_unit_2");\
    strcat(str, ",package_unit_3");\
    strcat(str, ",package_unit_4");\
    strcat(str, ",creation_date");\
    strcat(str, ",modification_date");\
    strcat(str, ",expiry_date");\
    strcat(str, ",out_of_market_date");\
    strcat(str, ",duration_months");\
    strcat(str, ",negative_list");\
    strcat(str, ",batch_article");\
    strcat(str, ",cooling_article");\
    strcat(str, ",narcotics");\
    strcat(str, ",fmd_relevant");\
    strcat(str, ",veterinary");\
    strcat(str, ",prescription_needed");\
    strcat(str, ",psychotrope");\
    strcat(str, ",zytostatic");\
    strcat(str, ",blocked");\
    strcat(str, ",not_allowed");\
    strcat(str, ",tax");\
    strcat(str, ",pharmacy_only");\
    strcat(str, ",medication");\
    strcat(str, ",toxic");\
    strcat(str, ",very_toxic");\
    strcat(str, ",harmful");\
    strcat(str, ",homeopathy");\
    strcat(str, ",medical_gases");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");

#define PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE(str) strcpy(str, "DELETE from cocp_stagein_article ");\
    strcat(str, " where ocp_article_no = ? and ((import_date < ?) or (import_date = ? and import_time < ? ))");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE(str) strcpy(str, "DELETE from cocp_stagein_article ");\
    strcat(str, " where ocp_article_no = ? and import_date = ? and import_time = ?");

    /* Prepare Insert/update/delete in cocp_stagein_articleprice */
#define PSQL_STR_INS_COCP_STAGEIN_ARTICLE_PRICE(str) strcpy(str, "INSERT into cocp_stagein_articleprice (");\
    strcat(str, " import_date");\
    strcat(str, ",import_time");\
    strcat(str, ",ocp_article_no");\
    strcat(str, ",valid_from_date");\
    strcat(str, ",manufacturer_base_price");\
    strcat(str, ",supplier_base_price");\
    strcat(str, ",pharmacy_base_price");\
    strcat(str, ",pharmacy_buy_price");\
    strcat(str, ",max_pharmacy_buy_price");\
    strcat(str, ",pharmacy_sell_price");\
    strcat(str, ",recom_pharmacy_sell_price");\
    strcat(str, ",max_pharmacy_sell_price");\
    strcat(str, ",manufacturer_percentage");\
    strcat(str, ",refund_amount");\
    strcat(str, ",vat_code");\
    strcat(str, ",price_type");\
    strcat(str, ",price_model");\
    strcat(str, ",discount_deduced_yet");\
    strcat(str, ",publication_number");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");

#define PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE_PRICE(str) strcpy(str, "DELETE from cocp_stagein_articleprice ");\
    strcat(str, " where  ocp_article_no = ? and (((import_date <> ? or import_time <> ?) and valid_from_date = ?))");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE_PRICE(str) strcpy(str, "DELETE from cocp_stagein_articleprice ");\
    strcat(str, " where ocp_article_no = ? and import_date = ? and import_time = ?");

    /* Prepare Insert/update/delete in cocp_stagein_article_france */
#define PSQL_STR_INS_COCP_STAGEIN_ARTICLE_FRANCE(str) strcpy(str, "INSERT into cocp_stagein_article_france (");\
    strcat(str, " import_date");\
    strcat(str, ",import_time");\
    strcat(str, ",ocp_article_no");\
    strcat(str, ",reimbursement_perc");\
    strcat(str, ",reimbursement_val");\
    strcat(str, ",unit_multiple");\
    strcat(str, ",qty_submultiple");\
    strcat(str, ",reserve_hosp");\
    strcat(str, ",reimbursement_type");\
    strcat(str, ",not_via_edi");\
    strcat(str, ",code_blocage");\
    strcat(str, ",code_lppr");\
    strcat(str, ",tfr_base_price");\
    strcat(str, ",distr_restr_export");\
    strcat(str, ",distr_restr_legal");\
    strcat(str, ",distr_restr_breizh");\
    strcat(str, ",distr_restr_hosp");\
    strcat(str, ",rebate_group_spec");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");

#define PSQL_STR_DEL_CLEAN_COCP_STAGEIN_ARTICLE_FRANCE(str) strcpy(str, "DELETE from cocp_stagein_article_france ");\
    strcat(str, " where ocp_article_no = ? and ((import_date < ?) or (import_date = ? and import_time < ? ))");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEIN_ARTICLE_FRANCE(str) strcpy(str, "DELETE from cocp_stagein_article_france ");\
    strcat(str, " where ocp_article_no = ? and import_date = ? and import_time = ?");

    /* Prepare Insert/update/delete in cocp_stagein_status */
#define PSQL_STR_INS_COCP_STAGEIN_STATUS(str) strcpy(str, "INSERT into cocp_stagein_status (");\
    strcat(str, " import_date");\
    strcat(str, ",import_time");\
    strcat(str, ",import_file");\
    strcat(str, ",import_code_records");\
    strcat(str, ",import_article_records");\
    strcat(str, ",import_price_records");\
    strcat(str, ",import_france_records");\
    strcat(str, ",import_attempt");\
    strcat(str, ",failed_code_records");\
    strcat(str, ",failed_article_records");\
    strcat(str, ",failed_price_records");\
    strcat(str, ",failed_france_records");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, 1, ?, ?, ?, ? )");

#define PSQL_STR_UPDATE_COCP_STAGEIN_STATUS(str) strcpy(str, "UPDATE cocp_stagein_status set ");\
    strcat(str, "import_date = ? ");\
    strcat(str, ",import_time = ? ");\
    strcat(str, ",import_file = ? ");\
    strcat(str, ",import_code_records = ? ");\
    strcat(str, ",import_article_records = ? ");\
    strcat(str, ",import_price_records = ? ");\
    strcat(str, ",import_france_records = ? ");\
    strcat(str, ",import_attempt = import_attempt + 1 ");\
    strcat(str, ",failed_code_records = ? ");\
    strcat(str, ",failed_article_records = ? ");\
    strcat(str, ",failed_price_records = ? ");\
    strcat(str, ",failed_france_records = ? ");\
    strcat(str, " where ");\
    strcat(str, " import_date = ? and import_time = ?");

    /* Prepare Insert/update/delete/select in cocp_stageout_article */
#define PSQL_STR_INS_COCP_STAGEOUT_ARTICLE(str) strcpy(str, "INSERT into cocp_stageout_article (");\
    strcat(str, " ocp_article_no");\
    strcat(str, ",article_no");\
    strcat(str, ",long_name");\
    strcat(str, ",unit");\
    strcat(str, ",dosage_form");\
    strcat(str, ",product_group");\
    strcat(str, ",product_type");\
    strcat(str, ",manufacturer_no");\
    strcat(str, ",supplier_no");\
    strcat(str, ",length");\
    strcat(str, ",width");\
    strcat(str, ",height");\
    strcat(str, ",weight");\
    strcat(str, ",package_unit_1");\
    strcat(str, ",package_unit_2");\
    strcat(str, ",package_unit_3");\
    strcat(str, ",package_unit_4");\
    strcat(str, ",creation_date");\
    strcat(str, ",modification_date");\
    strcat(str, ",expiry_date");\
    strcat(str, ",out_of_market_date");\
    strcat(str, ",duration_months");\
    strcat(str, ",negative_list");\
    strcat(str, ",batch_article");\
    strcat(str, ",cooling_article");\
    strcat(str, ",narcotics");\
    strcat(str, ",fmd_relevant");\
    strcat(str, ",veterinary");\
    strcat(str, ",prescription_needed");\
    strcat(str, ",psychotrope");\
    strcat(str, ",zytostatic");\
    strcat(str, ",blocked");\
    strcat(str, ",not_allowed");\
    strcat(str, ",tax");\
    strcat(str, ",pharmacy_only");\
    strcat(str, ",medication");\
    strcat(str, ",toxic");\
    strcat(str, ",very_toxic");\
    strcat(str, ",harmful");\
    strcat(str, ",homeopathy");\
    strcat(str, ",medical_gases");\
    strcat(str, ",season_group_1");\
    strcat(str, ",season_group_2");\
    strcat(str, ",season_group_3");\
    strcat(str, ",atc_code");\
    strcat(str, ",state_flags");\
    strcat(str, ",sum_state_flags");\
    strcat(str, ",username");\
    strcat(str, ",lastchange_date");\
    strcat(str, ",lastchange_time");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "\
                "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "\
                "?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

#define PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE(str) strcpy(str, "UPDATE cocp_stageout_article ");\
    strcat(str, "SET ocp_article_no=? ");\
    strcat(str, ",article_no=? ");\
    strcat(str, ",long_name=? ");\
    strcat(str, ",unit=? ");\
    strcat(str, ",dosage_form=? ");\
    strcat(str, ",product_group=? ");\
    strcat(str, ",product_type=? ");\
    strcat(str, ",manufacturer_no=? ");\
    strcat(str, ",supplier_no=? ");\
    strcat(str, ",length=? ");\
    strcat(str, ",width=? ");\
    strcat(str, ",height=? ");\
    strcat(str, ",weight=? ");\
    strcat(str, ",package_unit_1=? ");\
    strcat(str, ",package_unit_2=? ");\
    strcat(str, ",package_unit_3=? ");\
    strcat(str, ",package_unit_4=? ");\
    strcat(str, ",creation_date=? ");\
    strcat(str, ",modification_date=? ");\
    strcat(str, ",expiry_date=? ");\
    strcat(str, ",out_of_market_date=? ");\
    strcat(str, ",duration_months=? ");\
    strcat(str, ",negative_list=? ");\
    strcat(str, ",batch_article=? ");\
    strcat(str, ",cooling_article=? ");\
    strcat(str, ",narcotics=? ");\
    strcat(str, ",fmd_relevant=? ");\
    strcat(str, ",veterinary=? ");\
    strcat(str, ",prescription_needed=? ");\
    strcat(str, ",psychotrope=? ");\
    strcat(str, ",zytostatic=? ");\
    strcat(str, ",blocked=? ");\
    strcat(str, ",not_allowed=? ");\
    strcat(str, ",tax=? ");\
    strcat(str, ",pharmacy_only=? ");\
    strcat(str, ",medication=? ");\
    strcat(str, ",toxic=? ");\
    strcat(str, ",very_toxic=? ");\
    strcat(str, ",harmful=? ");\
    strcat(str, ",homeopathy=? ");\
    strcat(str, ",medical_gases=? ");\
    strcat(str, ",season_group_1=? ");\
    strcat(str, ",season_group_2=? ");\
    strcat(str, ",season_group_3=? ");\
    strcat(str, ",atc_code=? ");\
    strcat(str, ",state_flags=? ");\
    strcat(str, ",sum_state_flags=? ");\
    strcat(str, ",username=? ");\
    strcat(str, ",lastchange_date=? ");\
    strcat(str, ",lastchange_time=? ");\
    strcat(str, " where ocp_article_no=?");

// update stageout without updating manufacturer or supplier or product type
#define PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE2(str) strcpy(str, "UPDATE cocp_stageout_article ");\
    strcat(str, "SET ocp_article_no=? ");\
    strcat(str, ",article_no=? ");\
    strcat(str, ",long_name=? ");\
    /*strcat(str, ",unit=? ");\
    strcat(str, ",dosage_form=? ");\*/\
    strcat(str, ",product_group=? ");\
    /*strcat(str, ",product_type=? ");\
    strcat(str, ",manufacturer_no=? ");\
    strcat(str, ",supplier_no=? ");\*/\
    strcat(str, ",length=? ");\
    strcat(str, ",width=? ");\
    strcat(str, ",height=? ");\
    strcat(str, ",weight=? ");\
    strcat(str, ",package_unit_1=? ");\
    strcat(str, ",package_unit_2=? ");\
    strcat(str, ",package_unit_3=? ");\
    strcat(str, ",package_unit_4=? ");\
    strcat(str, ",creation_date=? ");\
    strcat(str, ",modification_date=? ");\
    strcat(str, ",expiry_date=? ");\
    strcat(str, ",out_of_market_date=? ");\
    strcat(str, ",duration_months=? ");\
    strcat(str, ",negative_list=? ");\
    strcat(str, ",batch_article=? ");\
    strcat(str, ",cooling_article=? ");\
    strcat(str, ",narcotics=? ");\
    strcat(str, ",fmd_relevant=? ");\
    strcat(str, ",veterinary=? ");\
    strcat(str, ",prescription_needed=? ");\
    strcat(str, ",psychotrope=? ");\
    strcat(str, ",zytostatic=? ");\
    strcat(str, ",blocked=? ");\
    strcat(str, ",not_allowed=? ");\
    strcat(str, ",tax=? ");\
    strcat(str, ",pharmacy_only=? ");\
    strcat(str, ",medication=? ");\
    strcat(str, ",toxic=? ");\
    strcat(str, ",very_toxic=? ");\
    strcat(str, ",harmful=? ");\
    strcat(str, ",homeopathy=? ");\
    strcat(str, ",medical_gases=? ");\
    strcat(str, ",season_group_1=? ");\
    strcat(str, ",season_group_2=? ");\
    strcat(str, ",season_group_3=? ");\
    strcat(str, ",atc_code=? ");\
    strcat(str, ",state_flags=? ");\
    strcat(str, ",sum_state_flags=? ");\
    strcat(str, ",username=? ");\
    strcat(str, ",lastchange_date=? ");\
    strcat(str, ",lastchange_time=? ");\
    strcat(str, " where ocp_article_no=?");

#define PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE(str) strcpy(str, "SELECT ocp_article_no,");\
    strcat(str, " article_no,");\
    strcat(str, " long_name,");\
    strcat(str, " unit,");\
    strcat(str, " dosage_form,");\
    strcat(str, " product_group,");\
    strcat(str, " product_type,");\
    strcat(str, " manufacturer_no,");\
    strcat(str, " supplier_no,");\
    strcat(str, " length,");\
    strcat(str, " width,");\
    strcat(str, " height,");\
    strcat(str, " weight,");\
    strcat(str, " package_unit_1,");\
    strcat(str, " package_unit_2,");\
    strcat(str, " package_unit_3,");\
    strcat(str, " package_unit_4,");\
    strcat(str, " creation_date, ");\
    strcat(str, " modification_date,");\
    strcat(str, " expiry_date,");\
    strcat(str, " out_of_market_date,");\
    strcat(str, " duration_months,");\
    strcat(str, " negative_list,");\
    strcat(str, " batch_article,");\
    strcat(str, " cooling_article,");\
    strcat(str, " narcotics,");\
    strcat(str, " fmd_relevant,");\
    strcat(str, " veterinary,");\
    strcat(str, " prescription_needed,");\
    strcat(str, " psychotrope,");\
    strcat(str, " zytostatic,");\
    strcat(str, " blocked,");\
    strcat(str, " not_allowed,");\
    strcat(str, " tax,");\
    strcat(str, " pharmacy_only,");\
    strcat(str, " medication,");\
    strcat(str, " toxic,");\
    strcat(str, " very_toxic,");\
    strcat(str, " harmful,");\
    strcat(str, " homeopathy,");\
    strcat(str, " medical_gases,");\
    strcat(str, " season_group_1,");\
    strcat(str, " season_group_2,");\
    strcat(str, " season_group_3,");\
    strcat(str, " atc_code,");\
    strcat(str, " state_flags,");\
    strcat(str, " sum_state_flags,");\
    strcat(str, " username,");\
    strcat(str, " lastchange_date,");\
    strcat(str, " lastchange_time ");\
    strcat(str, " FROM cocp_stageout_article ");\
    strcat(str, " where lastchange_date=? and lastchange_time=?");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE(str) strcpy(str, "DELETE from cocp_stageout_article ");\
    strcat(str, " where ocp_article_no=? and lastchange_date = ? and lastchange_time = ?");


    /* Prepare Insert/update/delete/select in cocp_stageout_articlecode */

#define PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_CODE(str) strcpy(str, "INSERT into cocp_stageout_articlecode (");\
    strcat(str, " ocp_article_no");\
    strcat(str, ",article_no");\
    strcat(str, ",code_type");\
    strcat(str, ",article_code");\
    strcat(str, ",preferred_flag");\
    strcat(str, ",date_changed");\
    strcat(str, ",state_flags");\
    strcat(str, ",sum_state_flags");\
    strcat(str, ",username");\
    strcat(str, ",lastchange_date");\
    strcat(str, ",lastchange_time");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

#define PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_CODE(str) strcpy(str, "UPDATE cocp_stageout_articlecode ");\
    strcat(str, "SET ocp_article_no=? ");\
    strcat(str, ",article_no=? ");\
    strcat(str, ",code_type=? ");\
    strcat(str, ",article_code=? ");\
    strcat(str, ",preferred_flag=? ");\
    strcat(str, ",date_changed=? ");\
    strcat(str, ",state_flags=? ");\
    strcat(str, ",sum_state_flags=? ");\
    strcat(str, ",username=? ");\
    strcat(str, ",lastchange_date=? ");\
    strcat(str, ",lastchange_time=? ");\
    strcat(str, " where ocp_article_no=? and article_no=? and code_type=?");

#define PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_CODE(str) strcpy(str, "SELECT ocp_article_no");\
    strcat(str, " ,article_no");\
    strcat(str, " ,code_type");\
    strcat(str, " ,article_code");\
    strcat(str, " ,preferred_flag");\
    strcat(str, " ,date_changed");\
    strcat(str, " ,state_flags");\
    strcat(str, " ,sum_state_flags");\
    strcat(str, " ,username");\
    strcat(str, " ,lastchange_date");\
    strcat(str, " ,lastchange_time");\
    strcat(str, " from cocp_stageout_articlecode");\
    strcat(str, " where ocp_article_no=? and lastchange_date=? and lastchange_time=?");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_CODE(str) strcpy(str, "DELETE from cocp_stageout_articlecode ");\
    strcat(str, " where ocp_article_no=? and lastchange_date = ? and lastchange_time = ?");

    /* Prepare Insert/update/delete/select in cocp_stageout_articleprice */

#define PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_PRICE(str) strcpy(str, "INSERT into cocp_stageout_articleprice (");\
    strcat(str, " ocp_article_no");\
    strcat(str, ",article_no");\
    strcat(str, ",valid_from_date");\
    strcat(str, ",manufacturer_base_price");\
    strcat(str, ",supplier_base_price");\
    strcat(str, ",pharmacy_base_price");\
    strcat(str, ",pharmacy_buy_price");\
    strcat(str, ",max_pharmacy_buy_price");\
    strcat(str, ",pharmacy_sell_price");\
    strcat(str, ",recom_pharmacy_sell_price");\
    strcat(str, ",max_pharmacy_sell_price");\
    strcat(str, ",manufacturer_percentage");\
    strcat(str, ",refund_amount");\
    strcat(str, ",vat_code");\
    strcat(str, ",price_type");\
    strcat(str, ",price_model");\
    strcat(str, ",discount_deduced_yet");\
    strcat(str, ",publication_number");\
    strcat(str, ",state_flags");\
    strcat(str, ",sum_state_flags");\
    strcat(str, ",username");\
    strcat(str, ",lastchange_date");\
    strcat(str, ",lastchange_time");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

#define PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_PRICE(str) strcpy(str, "UPDATE cocp_stageout_articleprice ");\
    strcat(str, "SET ocp_article_no=?");\
    strcat(str, ",article_no=?");\
    strcat(str, ",valid_from_date=?");\
    strcat(str, ",manufacturer_base_price=?");\
    strcat(str, ",supplier_base_price=?");\
    strcat(str, ",pharmacy_base_price=?");\
    strcat(str, ",pharmacy_buy_price=?");\
    strcat(str, ",max_pharmacy_buy_price=?");\
    strcat(str, ",pharmacy_sell_price=?");\
    strcat(str, ",recom_pharmacy_sell_price=?");\
    strcat(str, ",max_pharmacy_sell_price=?");\
    strcat(str, ",manufacturer_percentage=?");\
    strcat(str, ",refund_amount=?");\
    strcat(str, ",vat_code=?");\
    strcat(str, ",price_type=?");\
    strcat(str, ",price_model=?");\
    strcat(str, ",discount_deduced_yet=?");\
    strcat(str, ",publication_number=?");\
    strcat(str, ",state_flags=?");\
    strcat(str, ",sum_state_flags=?");\
    strcat(str, ",username=?");\
    strcat(str, ",lastchange_date=?");\
    strcat(str, ",lastchange_time=?");\
    strcat(str, " where ocp_article_no=? and valid_from_date=?");

#define PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_PRICE(str) strcpy(str, "SELECT ocp_article_no");\
    strcat(str, " ,article_no");\
    strcat(str, " ,valid_from_date");\
    strcat(str, " ,manufacturer_base_price");\
    strcat(str, " ,supplier_base_price");\
    strcat(str, " ,pharmacy_base_price");\
    strcat(str, " ,pharmacy_buy_price");\
    strcat(str, " ,max_pharmacy_buy_price");\
    strcat(str, " ,pharmacy_sell_price");\
    strcat(str, " ,recom_pharmacy_sell_price");\
    strcat(str, " ,max_pharmacy_sell_price");\
    strcat(str, " ,manufacturer_percentage");\
    strcat(str, " ,refund_amount");\
    strcat(str, " ,vat_code");\
    strcat(str, " ,price_type");\
    strcat(str, " ,price_model");\
    strcat(str, " ,discount_deduced_yet");\
    strcat(str, " ,publication_number");\
    strcat(str, " ,state_flags");\
    strcat(str, " ,sum_state_flags");\
    strcat(str, " ,username");\
    strcat(str, " ,lastchange_date");\
    strcat(str, " ,lastchange_time");\
    strcat(str, " from cocp_stageout_articleprice");\
    strcat(str, " where ocp_article_no = ? and valid_from_date = ? and lastchange_date=? and lastchange_time=?");

#define PSQL_STR_SELECT_ALL_DATEVALIDFROM_COCP_STAGEOUT_ARTICLE_PRICE(str) strcpy(str, "SELECT valid_from_date");\
    strcat(str, " from cocp_stageout_articleprice");\
    strcat(str, " where ocp_article_no = ? and  lastchange_date=? and lastchange_time=?");


#define PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_PRICE(str) strcpy(str, "DELETE from cocp_stageout_articleprice ");\
    strcat(str, " where ocp_article_no=? and lastchange_date = ? and lastchange_time = ?");

    /* Prepare Insert/update/delete/select in cocp_stageout_article_france */

#define PSQL_STR_INS_COCP_STAGEOUT_ARTICLE_FRANCE(str) strcpy(str, "INSERT into cocp_stageout_article_france (");\
    strcat(str, " ocp_article_no");\
    strcat(str, ",article_no");\
    strcat(str, ",reimbursement_perc");\
    strcat(str, ",reimbursement_val");\
    strcat(str, ",unit_multiple");\
    strcat(str, ",qty_submultiple");\
    strcat(str, ",reserve_hosp");\
    strcat(str, ",reimbursement_type");\
    strcat(str, ",not_via_edi");\
    strcat(str, ",code_blocage");\
    strcat(str, ",code_lppr");\
    strcat(str, ",tfr_base_price");\
    strcat(str, ",distr_restr_export");\
    strcat(str, ",distr_restr_legal");\
    strcat(str, ",distr_restr_breizh");\
    strcat(str, ",distr_restr_hosp");\
    strcat(str, ",rebate_group_spec");\
    strcat(str, ",state_flags");\
    strcat(str, ",sum_state_flags");\
    strcat(str, ",username");\
    strcat(str, ",lastchange_date");\
    strcat(str, ",lastchange_time");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

#define PSQL_STR_UPDATE_COCP_STAGEOUT_ARTICLE_FRANCE(str) strcpy(str, "UPDATE cocp_stageout_article_france ");\
    strcat(str, "SET ocp_article_no=?");\
    strcat(str, ",article_no=?");\
    strcat(str, ",reimbursement_perc=?");\
    strcat(str, ",reimbursement_val=?");\
    strcat(str, ",unit_multiple=?");\
    strcat(str, ",qty_submultiple=?");\
    strcat(str, ",reserve_hosp=?");\
    strcat(str, ",reimbursement_type=?");\
    strcat(str, ",not_via_edi=?");\
    strcat(str, ",code_blocage=?");\
    strcat(str, ",code_lppr=?");\
    strcat(str, ",tfr_base_price=?");\
    strcat(str, ",distr_restr_export=?");\
    strcat(str, ",distr_restr_legal=?");\
    strcat(str, ",distr_restr_breizh=?");\
    strcat(str, ",distr_restr_hosp=?");\
    strcat(str, ",rebate_group_spec=?");\
    strcat(str, ",state_flags=?");\
    strcat(str, ",sum_state_flags=?");\
    strcat(str, ",username=?");\
    strcat(str, ",lastchange_date=?");\
    strcat(str, ",lastchange_time=?");\
    strcat(str, " where ocp_article_no=?");

#define PSQL_STR_SELECT_DATETIME_COCP_STAGEOUT_ARTICLE_FRANCE(str) strcpy(str, "SELECT ocp_article_no");\
    strcat(str, " ,article_no");\
    strcat(str, " ,reimbursement_perc");\
    strcat(str, " ,reimbursement_val");\
    strcat(str, " ,unit_multiple");\
    strcat(str, " ,qty_submultiple");\
    strcat(str, " ,reserve_hosp");\
    strcat(str, " ,reimbursement_type");\
    strcat(str, " ,not_via_edi");\
    strcat(str, " ,code_blocage");\
    strcat(str, " ,code_lppr");\
    strcat(str, " ,tfr_base_price");\
    strcat(str, " ,distr_restr_export");\
    strcat(str, " ,distr_restr_legal");\
    strcat(str, " ,distr_restr_breizh");\
    strcat(str, " ,distr_restr_hosp");\
    strcat(str, " ,rebate_group_spec");\
    strcat(str, " ,state_flags");\
    strcat(str, " ,sum_state_flags");\
    strcat(str, " ,username");\
    strcat(str, " ,lastchange_date");\
    strcat(str, " ,lastchange_time");\
    strcat(str, " from cocp_stageout_article_france");\
    strcat(str, " where ocp_article_no = ? and lastchange_date=? and lastchange_time=?");

#define PSQL_STR_DEL_DATETIME_COCP_STAGEOUT_ARTICLE_FRANCE(str) strcpy(str, "DELETE from cocp_stageout_article_france ");\
    strcat(str, " where ocp_article_no=? and lastchange_date = ? and lastchange_time = ?");

    /* master data ******************/
    /* zartikel */
#define PSQL_STR_SELECT_EXIST_ARTICLE_ZARTIKEL(str) strcpy(str, "SELECT artikel_nr");\
    strcat(str, " from zartikel");\
    strcat(str, " where artikel_nr=?");
    /* artve */

#define PSQL_STR_SELECT_EXIST_PACKAGE_UNIT_ARTVE(str) strcpy(str, "SELECT artikel_nr");\
    strcat(str, " from artve");\
    strcat(str, " where artikel_nr=?");

    /* zartwg */
    /* Prepare insert/update/select season group (2,5,A,G) in pharmos zartwg (artikel_nr, art, warengruppe) */
 #define PSQL_STR_INS_SEASON_GROUP_ZARTWG(str) strcpy(str, "INSERT into zartwg (");\
    strcat(str, "artikel_nr");\
    strcat(str, ",art");\
    strcat(str, ",warengruppe");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, ?)");

#define PSQL_STR_UPDATE_SEASON_GROUP_ZARTWG(str) strcpy(str, "UPDATE zartwg ");\
    strcat(str, "SET artikel_nr=? ");\
    strcat(str, ",art=? ");\
    strcat(str, ",warengruppe=? ");\
    strcat(str, " where artikel_nr=? and art=?");

#define PSQL_STR_SELECT_SEASON_GROUP_ZARTWG(str) strcpy(str, "SELECT warengruppe FROM zartwg ");\
    strcat(str, " where artikel_nr=? and art=?");

#define PSQL_STR_SELECT_EXIST_SEASON_GROUP_ZARTWG(str) strcpy(str, "SELECT artikel_nr FROM zartwg ");\
    strcat(str, " where artikel_nr=? and art=?");

    /* zartpreis */
#define PSQL_STR_SELECT_ALL_DATAVALID_ARTTIKEL_NR_ZARTPREIS(str) strcpy(str, "SELECT datumgueltigab");\
    strcat(str, " from zartpreis");\
    strcat(str, " where artikel_nr=?");

#define PSQL_STR_SELECT_EXIST_PRICE_ZARTPREIS(str) strcpy(str, "SELECT artikel_nr");\
    strcat(str, " from zartpreis");\
    strcat(str, " where artikel_nr=? and datumgueltigab=?");

    /* zartfrance */
#define PSQL_STR_SELECT_EXIST_FRANCE_ZARTFRANCE(str) strcpy(str, "SELECT articleno");\
    strcat(str, " from zartfrance");\
    strcat(str, " where articleno=?");

    /* carticlecodes */
#define PSQL_STR_SELECT_EXIST_ARTICLECODES(str) strcpy(str, "SELECT articleno");\
    strcat(str, " from carticlecodes");\
    strcat(str, " where articleno=? and code_type=?");

#define PSQL_STR_SELECT_ALL_CODETYPE_ARTICLECODES(str) strcpy(str, "SELECT code_type");\
    strcat(str, " from carticlecodes");\
    strcat(str, " where articleno=?");

    /* zpznpflege */
 #define PSQL_STR_INS_ARTICLE_UPDATE_ZPZNPFLEGE(str) strcpy(str, "INSERT into zpznpflege (");\
    strcat(str, "artikel_nr");\
    strcat(str, ",datum");\
    strcat(str, ",dezap_sa");\
    strcat(str, ") values ");\
    strcat(str, "( ?, ?, 34)");


#endif // SQL_REQS_H_INCLUDED
