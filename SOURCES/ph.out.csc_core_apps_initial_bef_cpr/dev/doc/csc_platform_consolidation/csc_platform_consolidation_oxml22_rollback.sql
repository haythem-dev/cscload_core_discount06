--------------------------------------------
-- To be used on OXML22                   --
-- Replace <?F> with the correct branchno --
--------------------------------------------

UPDATE ode21@ode21s_oxml22_tcp:rechner 
	SET datenbank_name='ode22@ode22s_oxml22_tcp' WHERE filialnr=<?F>;
	
UPDATE ode22@ode22s_oxml22_tcp:rechner 
	SET datenbank_name='ode22@ode22s_oxml22_tcp' WHERE filialnr=<?F>;
	
	
	
    
            