select * from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1)


select * from ccodetypes


insert into ccodetypes (code_type, name, max_number, code_length, artnr_substitute) values ('8', 'CETIN', 1, 13, 1);
insert into ccodetypes (code_type, name, max_number, code_length, artnr_substitute) values ('9', 'ACL', 1, 13, 1);
insert into ccodetypes (code_type, name, max_number, code_length, artnr_substitute) values ('10', 'TIERARZNEI', 1, 14, 1);
insert into ccodetypes (code_type, name, max_number, code_length, artnr_substitute) values ('11', 'PZN 7', 1, 7, 1);


insert into carticlecodes (ArticleNo, code_type, article_code, serial_number
--   , preferred_flag
) values (112, 9, '123', 0
--   , 1
)
